#include <apt-pkg/algorithms.h>
#include <apt-pkg/depcache.h>

APT_HIDDEN struct PboSolver
{
   /// Allows us to lookup versions by id
   std::vector<pkgCache::VerIterator> versions;
   /// Needed to figure out the list of versions in the closure belonging to a package
   std::vector<pkgCache::VerIterator> *packages;
   /// Mapping of dep
   int *dep_depth;
   int iteration;

   bool Setup(pkgDepCache &Cache);
};
