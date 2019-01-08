//PROGRAM TIP_Coulex_RDM

#include "G4RunManager.hh"
#include "G4UImanager.hh"

//#ifdef G4UI_USE_ROOT
//#include "G4UIRoot.hh"
//#else
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
//#endif

#ifdef G4UI_USE_XM
#include "G4UIXm.hh"
#endif

#ifdef G4VIS_USE
#include "VisManager.hh"
#endif

#include "DetectorConstruction.hh"
#include "DetectorConstruction_Messenger.hh"
#include "Projectile.hh"
#include "Projectile_Messenger.hh"
#include "Recoil.hh"
#include "Recoil_Messenger.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "Results.hh"
#include "Results_Messenger.hh"
#include "RunAction.hh"
#include "Run_Messenger.hh"
#include "EventAction.hh"
#include "EventAction_Messenger.hh"
#include "SteppingAction.hh"

int main(int argc,char** argv) 
{
  // Seed the random number generator manually
  G4long myseed = time(NULL);

  // Preset seed (runs the same every time)
  // G4long myseed=1388637269;

  CLHEP::HepRandom::setTheSeed(myseed);
  G4cout<<" Seed set to  "<<myseed<<G4endl;
  // getc(stdin);

  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;
 
  // set mandatory initialization classes
  DetectorConstruction* theDetector=new DetectorConstruction();
  runManager->SetUserInitialization(theDetector);
  DetectorConstruction_Messenger* detectorMessenger;
  detectorMessenger = new DetectorConstruction_Messenger(theDetector);
  // theDetector->Report();
 
  // Construct the incoming beam
  Projectile* theProjectile=new Projectile();
  Projectile_Messenger* ProjectileMessenger;
  ProjectileMessenger=new Projectile_Messenger(theProjectile);
  theProjectile->Report();

 // Construct the outgoing beam
  Recoil* theRecoil=new Recoil();
  Recoil_Messenger* RecoilMessenger;
  RecoilMessenger=new Recoil_Messenger(theRecoil);
  theRecoil->Report();

  // set mandatory user action clas
  PhysicsList *thePhysicsList = new PhysicsList(theProjectile,theRecoil);
  runManager->SetUserInitialization(thePhysicsList); 
  
  Run_Messenger *runMessenger;
  runMessenger = new Run_Messenger(runManager, thePhysicsList);
 
  PrimaryGeneratorAction* generatorAction= new PrimaryGeneratorAction(theDetector,theProjectile);
  runManager->SetUserAction(generatorAction);

  Results* results = new Results(theProjectile,theRecoil,theDetector);
  Results_Messenger* resultsMessenger;
  resultsMessenger = new Results_Messenger(results);

  RunAction* theRunAction=new RunAction(thePhysicsList,results,theDetector);
  runManager->SetUserAction(theRunAction);
 
  EventAction* eventAction = new EventAction(results,theRunAction,theProjectile,theRecoil,theDetector);
  //EventAction* eventAction = new EventAction(results,theRunAction);
  runManager->SetUserAction(eventAction);
  EventAction_Messenger* eventActionMessenger;
  eventActionMessenger = new EventAction_Messenger(eventAction);

  SteppingAction* stepAction = new SteppingAction(theDetector,eventAction);
  runManager->SetUserAction(stepAction);

  //G4UIsession* session=0;
  // get the pointer to the UI manager and set verbosities
  G4UImanager *UI = G4UImanager::GetUIpointer();

#ifdef G4VIS_USE  
 G4VisManager* visManager = new VisManager; 
 // visualization manager
 visManager->Initialize();
#endif

  if (argc == 1) // Define UI session for interactive mode.
  {

    /*#ifdef G4VIS_USE
    // visualization manager
    visManager->Initialize();
    #endif

    // G4UIterminal is a (dumb) terminal.
    #ifdef G4UI_USE_ROOT
    // G4URoot is a ROOT based GUI.
    session = new G4UIRoot(argc,argv);
    #else
    #ifdef G4UI_USE_XM
    session = new G4UIXm(argc,argv);
    #else
    #ifdef G4UI_USE_TCSH
    session = new G4UIterminal(new G4UItcsh);
    #else
    session = new G4UIterminal();
    #endif
    #endif
    #endif*/
    G4cout << "TIP_Coulex_RDM macro_file" << G4endl;
    G4cout << "---------------------------------" << G4endl;
    G4cout << "Please specify a macro file (.mac) to run as an argument."
           << G4endl;
    exit(-1);
  } else {
    // check whether the macro file exists
    FILE *file;
    file = fopen(argv[1], "r");
    if (file) {
      fclose(file);
    } else {
      G4cout << "ERROR: macro file " << argv[1] << " cannot be opened."
             << G4endl;
      G4cout << "Please check whether the file exists." << G4endl;
      exit(-1);
    }
  }

  /*if (session)   // Define UI session for interactive mode.
    {
      // G4UIterminal is a (dumb) terminal.

      #ifdef G4UI_USE_XM
      //   Customize the G4UIXm menubar with a macro file :
           UI->ApplyCommand("/control/execute gui/gui.mac");
      #endif
      session->SessionStart();
      delete session;
    }
  else           // Batch mode
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UI->ApplyCommand(command+fileName);
    }
  if(argc==1)
    {
      #ifdef G4VIS_USE
      delete visManager;
      #endif
    }*/

  G4String command = "/control/execute ";
  G4String fileName = argv[1];
  UI->ApplyCommand(command + fileName);

  // job termination
  delete detectorMessenger;
  delete ProjectileMessenger;
  delete RecoilMessenger;
  delete resultsMessenger;
  delete runMessenger;
  delete eventActionMessenger; 
  delete runManager;
#ifdef G4VIS_USE
  delete visManager;
#endif
  
  return 0;
}
