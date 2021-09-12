#!/bin/bash
#SBATCH --job-name=subm100
#SBATCH --ntasks=1
#SBATCH --nodes=1
#SBATCH --time=01:00:00
#SBATCH	-p serial
#SBATCH --mem-per-cpu=3700
#a partição pode ser "long" (14 dias) e "medium*" (4 dias)

#Este script submete um array de scripts "meuJobArray.sh"

# Carregando módulos ROOT e Garfield++
module load gnu8/8.3.0
module load root-6.16.00-gcc-8.3.0-ih7ao2c
module load garfieldpp/3.0

# Compilando o programa gem.C
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$GARFIELD_HOME/build
make

# Linha de execução do seu experimento
echo "Submetendo job array..."
sbatch --array=0-10 meuJobArray.sh




