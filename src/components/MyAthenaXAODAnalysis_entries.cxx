#include "GaudiKernel/DeclareFactoryEntries.h"

#include "../MyAthAnalysisAlg.h"

DECLARE_ALGORITHM_FACTORY( MyAthAnalysisAlg )

DECLARE_FACTORY_ENTRIES( MyAthenaXAODAnalysis ) 
{
  DECLARE_ALGORITHM( MyAthAnalysisAlg );
}
