///////////////////////// -*- C++ -*- /////////////////////////////
// MyAthAnalysisAlg.cxx 
// Implementation file for class MyAthAnalysisAlg
// Author: S.Binet<binet@cern.ch>
/////////////////////////////////////////////////////////////////// 

// MyAthenaXAODAnalysis includes
#include "MyAthAnalysisAlg.h"

// STL includes

// FrameWork includes
#include "GaudiKernel/Property.h"

// EDM includes
#include "xAODEventInfo/EventInfo.h"
#include "xAODJet/JetContainer.h"
#include "xAODJet/JetAuxContainer.h"



/////////////////////////////////////////////////////////////////// 
// Public methods: 
/////////////////////////////////////////////////////////////////// 

// Constructors
////////////////
MyAthAnalysisAlg::MyAthAnalysisAlg( const std::string& name, 
			  ISvcLocator* pSvcLocator ) : 
  ::AthHistogramAlgorithm( name, pSvcLocator )
{
  //
  // Property declaration
  // 
  //declareProperty( "Property", m_nProperty );

}

// Destructor
///////////////
MyAthAnalysisAlg::~MyAthAnalysisAlg()
{}

// Athena Algorithm's Hooks
////////////////////////////
StatusCode MyAthAnalysisAlg::initialize()
{
  ATH_MSG_INFO ("Initializing " << name() << "...");

  return StatusCode::SUCCESS;
}

StatusCode MyAthAnalysisAlg::finalize()
{
  ATH_MSG_INFO ("Finalizing " << name() << "...");

  return StatusCode::SUCCESS;
}

StatusCode MyAthAnalysisAlg::execute()
{  
  ATH_MSG_DEBUG ("Executing " << name() << "...");

  // Event information
  const xAOD::EventInfo* eventInfo = 0;

  // Get the container from the event store
  // Don't need to pass the key name if only one container of that type
  ATH_CHECK( evtStore()->retrieve(eventInfo) );

  // Check if data or MC
  if(!eventInfo->eventType(xAOD::EventInfo::IS_SIMULATION)){
    ATH_MSG_DEBUG("DATA. Will continue to the next event.");
    return StatusCode::SUCCESS;
  }

  // Extra event-level info you might need
  int datasetID = eventInfo->mcChannelNumber();
  double eventWeight = eventInfo->mcEventWeight();

  // Analyzing jets
  const xAOD::JetContainer* jets = 0;
  ATH_CHECK( evtStore()->retrieve(jets, "AntiKt4LCTopoJets") );

  xAOD::JetContainer* goodJets = new xAOD::JetContainer;
  goodJets->setStore(new xAOD::JetAuxContainer);

  for(auto jetItr = jets->begin(); jetItr != jets->end(); ++jetItr){
    ATH_MSG_INFO( "  jet eta = " << (*jetItr)->eta() );
    if(fabs((*jetItr)->eta()) > 2.5) continue;

    xAOD::Jet* newJet = new xAOD::Jet;
    // Create private auxstore for the object, copying all values from old jet
    newJet->makePrivateStore(**jetItr);
    // Decorate with dummy variable
    newJet->auxdata<double>("myDouble") = 5.;
    goodJets->push_back(newJet);
  }

  // Record good jets to storegate
  ATH_CHECK( evtStore()->record(goodJets, "GoodJets") );
  ATH_CHECK( evtStore()->record(goodJets->getStore(), "GoodJetsAux.") );

  return StatusCode::SUCCESS;
}

/////////////////////////////////////////////////////////////////// 
// Const methods: 
///////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////// 
// Non-const methods: 
/////////////////////////////////////////////////////////////////// 

/////////////////////////////////////////////////////////////////// 
// Protected methods: 
/////////////////////////////////////////////////////////////////// 

/////////////////////////////////////////////////////////////////// 
// Const methods: 
///////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////// 
// Non-const methods: 
/////////////////////////////////////////////////////////////////// 


