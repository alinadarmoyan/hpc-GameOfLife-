THREADS="${1:-1}"
PROCS="${2:-1}"
export OMP_NUM_THREADS=$THREADS

make && mpirun -n $PROCS --oversubscribe --allow-run-as-root ./main
rm -f /home/common/.lock