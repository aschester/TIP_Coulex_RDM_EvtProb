# TIP Coulex-RDM Geant4 code

Maintainer: Aaron Chester

## Description

GEANT4 code implementing TIP/TIGRESS RDM using a single-step Coulex.

At present, the TIP CsI wall/ball and GRIFFIN/TIGRESS array geometries are implemented.

This code requires GEANT4 version 10.x (see the version 9.4 branch for the most recent code compatible with version 9).  If the ROOT interface is needed, the code in the version 9.4 branch should be used instead.

## Installation

This code has been tested with GEANT4.10.3.p03 on Centos 7.

This program depends on GEANT4.10.3.p03, ROOT (results are saved to ROOT tree files), and cmake.  These programs should be compiled from source and installed according to the install guides on their respective websites. ROOT version 5.x and cmake 2.6.2 or later are required; ROOT 6.10.04 and cmake 3.6.3 were used on the Centos machine the code was originally developed on. GEANT4 should be built with its data files, using the `-DGEANT4_INSTALL_DATA=ON` switch specified in its install guide.

Environment variables must be properly set up for all dependencies, for example by adding the following lines to ~/.bashrc (substituting the appropriate paths):

```
#ROOT configuration
export ROOTSYS=/path/to/root
export ROOTINC=/path/to/root/include
export ROOTLIB=/path/to/root/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ROOTLIB
export PATH=$PATH:$ROOTSYS/bin
```

```
#for GEANT4
export G4INSTALL=/path/to/geant4_install_directory
source $G4INSTALL/bin/geant4.sh
#substitute GEANT4_VERSION in the next line with the appropriate directory
source $G4INSTALL/share/GEANT4_VERSION/geant4make/geant4make.sh
```

The program is then compiled from source using the following commands (substituting the appropriate directories):

```
cmake -DGeant4_DIR=/path/to/geant4_install_directory/lib/GEANT4_VERSION
make
```

## Using the program

The program `TIP_Coulex_RDM` is run from the command line and takes a batch file as its only argument.  The batch file contains a list of commands which are executed in order by the program.  See the included sample batch file "94Sr_Al_target_Cu_stopper.mac" for examples of commands that can be used in the simulation.  

### Data Generation and Saving

|**Command**|**Effect**|
|:---:|:---:|
| /run/beamOn NUMBER | Runs the simulation for the specified number of events (primary beam tracks). |
| /Results/Tree/Save FILENAME | Saves the results of the simulation to a ROOT tree in the specified file. |

## Other Notes

Some GEANT4 classes have been backported from version 9.4 for use in this code:

G4IonParametrisedLossModel (from GEANT4.9.4) - modified to allow for user defined stopping powers.

G4IonStoppingData (from GEANT4.9.4) - modified to allow for user defined stopping powers.

G4NuclearDecayChannel (from GEANT4.9.4) - reimplemented as GammaDecayChannel, a decay channel with only internal conversion.  This is done to properly compute properties of daughter nuclei and emitted gammas when considering a cascade of internal conversion decays.

G4Decay (from GEANT4.10.3) - modified to suppress warnings.

## Acknowledgements

J. Willaims - Compatibility with Geant4 v10.x, CsI ball implementation 

T. Ma - CsI ball code.

C. Morse - Finding and fixing memory leaks.

K. Starosta - Initial TIP codebase.

GRIFFIN/TIGRESS code based on code provided by the GRIFFIN collaboration, available at: https://github.com/GRIFFINCollaboration/detectorSimulations
