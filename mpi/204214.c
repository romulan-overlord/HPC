//Implement One-to-all Broadcast in ring of p processes, for any p > 2 and from any source.
//implementation that works for p = power of 2, from any source, 10 Marks
//implementation that works for any p, from any source, 10 Marks

#include <stdio.h>
#include <mpi.h>
#include<math.h>


//this works for any number os processes, but source must be less than nearest power of 2
void One2AllBCast(void *buf, int count, MPI_Datatype dp, int src, MPI_Comm comm){
  int dst = 0, source = 0, rank = 0, size = 0, v_id = 0, d = 0,j;
  double realD = 0;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);
  MPI_Status status;

  v_id = rank ^ src;
  d = (int)log2(size);
  realD = log2(size);
  // d = size - size % 
  d = (int)log2(size);
  int mask = (int)(pow(2,d)) - 1;
  // printf("%d is mask\n", mask);
  if( v_id < (int)pow(2,d)){
    for( int i = d-1; i >= 0; i--){
      mask = mask ^ (int)pow(2,i);
      // printf("%d is new mask for %d\n", mask, my_id);
      if((v_id & mask) == 0){
        // printf("%d passed first if at mask = %d\n", my_id, mask);
        if((v_id & (int)pow(2,i)) == 0){
          dst = v_id ^ (int)pow(2,i);
          dst = dst ^ src;
          // printf("i am %d sending to %d\n", rank, dst);
          MPI_Send(buf, count, dp, dst, 1, comm);
        } else {
          source = v_id ^ (int)pow(2,i);
          source = source ^ src;
          // printf("i am %d receiving from %d\n", rank, source);
          MPI_Recv(buf, count, dp, source, 1, comm, &status);
        }
      }
    }
  }
  if(realD - (double)d != 0){
    if(rank < (int)pow(2,d) && (rank + (int)pow(2,d)) < size){
      printf("i am %d sending to %d\n", rank, rank + (int)pow(2,d));
      MPI_Send(buf, count, dp, (rank + (int)pow(2,d)), 1, comm);
    }else if(rank >= (int)pow(2,d)){
      // printf("i am %d receiving from %d\n", rank, rank % (int)pow(2,d));
      MPI_Recv(buf, count, dp, (rank % (int)pow(2,d)), 1, comm, &status);
    }

  }
}

void One2AllBCast_2(void *buf, int count, MPI_Datatype dp, int src, MPI_Comm comm){
  int dst = 0, source = 0, rank = 0, size = 0, v_id = 0, d = 0, mRank = 0, mSrc = 0, j, temp = 0;
  double realD = 0;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);
  MPI_Status status;
  mRank = rank;
  for(j = 0; j < size - src; j++){
    mRank++;
    if(mRank == size)
      mRank = 0;
  }

  if(rank == src)
    mSrc = mRank;

  // printf("i am really %d mapped to %d\n", rank, mRank);
  
  // printf("i am really %d unmapped to %d\n", rank, temp);
  // printf("\nhelp:%d\n", (int)pow(2,d) - 1);


  d = (int)log2(size);
  realD = log2(size);

  int mask = (int)(pow(2,d)) - 1;

  if( mRank < (int)pow(2,d)){
    for( int i = d-1; i >= 0; i--){
      mask = mask ^ (int)pow(2,i);
      if((mRank & mask) == 0){
        if((mRank & (int)pow(2,i)) == 0){
          dst = mRank ^ (int)pow(2,i);
          temp = dst;
          for(j = 0; j < size - src; j++){
            temp--;
            if(temp < 0)
              temp = size -1;
          }
          printf("i am %d sending to %d that was originally %d\n", rank, temp, dst);
          MPI_Send(buf, count, dp, dst ^ mSrc, 1, comm);
        } else {
          source = mRank ^ (int)pow(2,i);
          temp = source;
          for(j = 0; j < src; j++){
            temp--;
            if(temp < 0)
              temp = size -1;
          }
          printf("i am %d receiving from %d that was originally %d\n", rank, temp, source);
          MPI_Recv(buf, count, dp, source ^ mSrc, 1, comm, &status);
        }
      }
    }
  }
  // if(realD - (double)d != 0){
  //   if(v_id < (int)pow(2,d) && (v_id + (int)pow(2,d)) < size){
  //     // printf("i am %d sending to %d\n", rank, rank + (int)pow(2,d));
  //     // MPI_Send(buf, count, dp, (v_id + (int)pow(2,d)) ^ src, 1, comm);
  //   }else if(rank >= (int)pow(2,d)){
  //     // printf("i am %d receiving from %d\n", rank, rank % (int)pow(2,d));
  //     // MPI_Recv(buf, count, dp, (v_id % (int)pow(2,d)) ^ src, 1, comm, &status);
  //   }

  // }
}

int main(int argc, char **argv)
{
  int rank= 0, size= 0, i = 0, src = 3;
  int arr[10]= {};
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  if(rank == src)
    for(i= 0; i < 10; i++)
      arr[i]= 3*i;

  // One-to-all-bcast(arr,10,MPI_INT,3,MPI_COMM_WORLD);

  // if(rank == 0)
  // for(i= 0; i < 10; i++)
  //   arr[i]= 3*i;

  One2AllBCast(arr,10,MPI_INT,src,MPI_COMM_WORLD);
  

  // for(i= 0; i < 10; i++)
    printf("%d got %d\n",rank,arr[5]);
  MPI_Finalize();
}
