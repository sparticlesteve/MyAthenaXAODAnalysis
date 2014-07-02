theApp.EvtMax = 5
svcMgr += CfgMgr.AthenaEventLoopMgr(EventPrintoutInterval=1)

# Put my algo on the sequence
algseq = CfgMgr.AthSequencer('AthAlgSeq')
algseq += CfgMgr.MyAthAnalysisAlg()

# Input files
import AthenaPoolCnvSvc.ReadAthenaPool
svcMgr.EventSelector.InputCollections = [ "/afs/cern.ch/atlas/project/PAT/xAODs/r5534/valid2.117050.PowhegPythia_P2011C_ttbar.digit.AOD.e2657_s1933_s1964_r5534/AOD.01482225._000107.pool.root.1" ]

# Output file
from OutputStreamAthenaPool.MultipleStreamManager import MSMgr
outStream = MSMgr.NewPoolRootStream("MyXAODStream", "myXAOD.pool.root")
outStream.AddItem(['xAOD::JetContainer_v1#GoodJets'])
outStream.AddItem(['xAOD::JetAuxContainer_v1#GoodJetsAux.'])
