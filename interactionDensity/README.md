# interactionDensity
Geant4 simulation of the interaction "density" of a 6 keV photon passing through noble gas mixtures.

Flags:
--debug runs program on verbose mode

--gases flag used to select the gases in the noble mixture. Example of use: "--gases=xna 0.7;0.2;.01", whe xna stands for Xenon, Neon and Argon and the comma separeted values are their concentrations. Note that the sum of the concentrations must equal 1.0.

--vis runs program on visualization mode

--prompt runs program on interactive mode

--events sets the number of events in the run, default value is 10.000. Example of use: --events 100