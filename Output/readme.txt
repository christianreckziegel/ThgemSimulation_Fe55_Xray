Over the time of work the data storage structure changed a few times and simulations were done between these times:  
1st  
First result: first simulation with no distinction between primary X-ray gammas and fluorescence gammas in storage  
2nd  
Primary gamma electrons: simulation of electrons generated only from primary X-rays from particle gun at Geant4  
Fluorescence electrons: simulation of electrons generated only from fluorescence X-rays  
3rd  
Fluorescence full set: simulation of electrons generated only from fluorescence, storing also the electron initial   energy this time  


Calibration is the resulting output from the Calibration Garfield++ folder, the calibration curve is constructed


ArParticles.root is the most recent version of the output simulated at Geant4 which is input at Garfield++  
mergeFiles.C merge the inumerous output data from each job simulation at titanio cluster in one final file  
lerResult.C, resultAlaysys.C and calibrationAnalysis.C are analysis template macros for each case  


