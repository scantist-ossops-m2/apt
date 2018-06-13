#include <apt-pkg/pbo-solver.h>

bool PboSolver::Setup(pkgDepCache &Cache)
{
   // Let's over compensate
   dep_depth = new int[Cache.Head().DependsCount];
   packages = new std::vector<pkgCache::VerIterator>[Cache.Head().PackageCount];

   // Push initital set - set of installed and changed packages / versions
   for (pkgCache::PkgIterator P = Cache.PkgBegin(); P.end() == false; ++P)
   {
      if ((Cache[P].Keep() && !P->CurrentVer))
	 continue;

      for (pkgCache::VerIterator V = P.VersionList(); V.IsGood() && V.end() == false; V++)
      {
	 versions.push_back(V);
	 packages[P->ID].push_back(V);
      }
   }

   // Determine closure
   auto length = versions.size();
   std::unique_ptr<bool[]> seen(new bool[Cache.Head().VersionCount]);
   for (iteration = 0; true; iteration++)
   {
      for (int i = 0; i < length; i++)
      {
	 auto ver = versions[i];
	 if (seen[ver->ID] == true)
	    continue;

	 seen[ver->ID] = true;
	 for (auto dep = ver.DependsList(); !dep.end(); dep++)
	 {
	    // FIXME: Only need to record first depth;
	    dep_depth[dep->ID] = iteration;

	    auto targets = dep.AllTargets();

	    if (targets[0] == nullptr)
	       continue;

	    for (auto target_it = &targets[0]; *target_it != nullptr; target_it++)
	    {
	       auto target = pkgCache::VerIterator(Cache, *target_it);
	       versions.push_back(target);
	       packages[target.ParentPkg()->ID].push_back(target);
	    }
	 }
      }

      if (versions.size() == length)
      {
	 break;
      }

      length = versions.size();
   }
}
