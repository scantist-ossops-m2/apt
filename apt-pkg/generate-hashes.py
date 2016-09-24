import collections, sys

class Trie(object):

    count = 0

    def __init__(self):
        self.key = None
        self.value = None
        self.children = dict()

    def insert(self, key, k):
        if not key:
            self.key = key
            Trie.count += 1
            self.value = Trie.count
            return
        if key[0] not in self.children:
            self.children[key[0]] = Trie()

        self.children[key[0]].insert(key[1:], k)

    def print_table(self, index=0):
        print(index * "    ", "switch(%d < length ? string[%d] : 0) {" % (index, index))
        for key, sub in sorted(self.children.items()):
            print(index * "    ", """case '%c':""" % key.lower())
            if key.upper() != key.lower():
                print(index * "    ", """case '%c':""" % key.upper())
            sub.print_table(index = index + 1)

        if self.value is not None:
            assert self.value != 0
            print(index * "    ", 'case 0: return %d;' % self.value)

        print(index * "    ", 'default: return 0;')
        print(index * "    ", "}")

    def print_words(self, sofar=None):
        if sofar is None:
            sofar = []
        if self.key is not None:
            key = "".join(sofar)
            key = key.replace("-", "_")
            print(key, "=", self.value, ",")
        for key, sub in sorted(self.children.items()):
            sub.print_words(sofar + [key])

words = Trie()

for line in open(sys.argv[1]):
    words.insert(line.strip(), line.strip())

print("#include <stddef.h>")
print("static unsigned int PerfectHashMax = ", Trie.count, ";")
print("static unsigned int PerfectHash(const char *string, size_t length)")
print("{")
words.print_table()
print("}")
print("enum class PerfectKey {")
words.print_words()
print("};")
