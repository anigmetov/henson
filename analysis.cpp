#include <cstdio>
#include <cassert>
#include <unistd.h>
#include <mpi.h>

#include <henson/data.h>
#include <henson/context.h>

int main(int argc, char** argv)
{
    MPI_Comm world = henson_get_world();

    int rank, size;
    MPI_Comm_rank(world, &rank);
    MPI_Comm_size(world, &size);

    int t = 0;
    while(true)
    {
        sleep(rank);

        float* data;
        size_t count;
        size_t type;
        size_t stride;
        henson_load_array("data", (void**) &data, &type, &count, &stride);
        assert(type == sizeof(float));

        float sum = 0;
        for (size_t i = 0; i < count; ++i)
            sum += data[i];

        printf("Analysis   [t=%d]: rank = %d out of %d : sum = %f\n", t, rank, size, sum);

        henson_yield();
        ++t;
    }

    return 0;
}
