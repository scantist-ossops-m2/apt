/*
 * Copyright (C) 2016 Julian Andres Klode <jak@debian.org>
 *
 * R
 */
#ifndef APT_TRIE_H
#define APT_TRIE_H

#include <stdint.h>
#include <stddef.h>

#include <vector>
#include <string>

#include <apt-pkg/macros.h>

namespace APT {

/**
 * \brief A trie that can efficiently be cleared.
 *
 * In order to be cleared efficiently, this trie gives each node an id and
 * keeps a bitset mapping those ids to a bit indicating if the node has a value
 * set or not. This means that clearing the trie only requires clearing the
 * bitset (which can be done super fast), and not the tree.
 */
template<typename ValueType> APT_HIDDEN class Trie {
   /** \brief A node in the trie */
   struct node {
      /** \brief The id of the node, used by the bitset */
      unsigned int id;
      /** \brief Children of the node */
      node *next[256] = {0};
      /** \brief Constructor with explicit id information */
      node(size_t id) : id(id) {}

      ~node() {
	 for (size_t i = 0; i < sizeof(next) / sizeof(next[0]); i++)
	    delete next[i];
      }
   };

   /** A value that may be set or unset */
   struct Value {
      bool isDefined;
      ValueType value;
   };

   /** \brief The root node (id 0) */
   node root;

   /** \brief Values of nodes */
   std::vector<Value> values;

   /** \brief The next free node id */
   unsigned int next_node_id = 1;

   /**
    * \brief Finds the node for the given key
    *
    * This function finds the node for the given key, and can optionally create
    * the node and any intermediate nodes if the node does not yet exist.
    *
    * \tparam create If this find_node() instantation shall generate nodes
    * \param begin Beginning of the key
    * \param end End of the key (e.g. the NUL byte)
    */
   template<bool create> node *find_node(const char *begin, const char *end)
   {
      node *cur = &root;

      for (const char *c = begin; c < end; c++)
      {
	 int v = tolower_ascii(*c);
	 if (cur->next[v] == nullptr)
	 {
	    if (create)
	       cur->next[v] = new node(next_node_id++);
	    else
	       return nullptr;
	 }
	 cur = cur->next[v];
      }

      return cur;
   }

public:
   /** \brief Constructor */
   Trie() : root(0) {
   }
   /**
    * \brief Inserts a value into the trie at key
    *
    * \param begin The start of the key
    * \param end The end of the key
    * \param value Value to store in the trie
    */
   void insert(const char *begin, const char *end, ValueType value)
   {
      node *nod = find_node<true>(begin, end);

      if (nod->id >= values.size())
         values.resize(nod->id + 1);

      values[nod->id].isDefined = true;
      values[nod->id].value = value;
   }

   /**
    * \brief Finds a value stored for the given key
    *
    * \param begin The start of the key
    * \param end The end of the key
    * \param value Output variable where the value is to be stored to
    * \return true if the value exists, false otherwise.
    */
   bool find(const char *begin, const char *end, ValueType &value)
   {
      const node *nod = find_node<false>(begin, end);

      if (nod == nullptr || nod->id > values.size() || !values[nod->id].isDefined)
      {
	 value = ValueType();
	 return false;
      }

      value = values[nod->id].value;
      return true;
   }

   /** \brief Convenience interface for more complex insert() */
   void insert(std::string const &s, ValueType value)
   {
      insert(s.data(), s.data() + s.size(), value);
   }

   /** \brief Convenience interface for more complex find() */
   bool find(std::string const &s, ValueType& value)
   {
      return find(s.data(), s.data() + s.size(), value);
   }

   /**
    * \brief Remove all values from the trie.
    *
    * This keeps the data structure unmodified, it just resets the bitmap
    * which is checked if a value exists for a node.
    */
   void clear() {
      values.clear();
   }
};

};

#endif
