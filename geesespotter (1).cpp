#include "geesespotter_lib.h"

char *createBoard(std::size_t xdim, std::size_t ydim) {
  char *array{new char[xdim * ydim]{}};
  for (int i = 0; i < xdim * ydim; i++) {
    array[i] = 0;
  }
  return array; // you need to return an array in order to keep the program
                // running!
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim) {
  char hiddenBit(); // ob100000
  for (int i = 0; i < xdim * ydim; i++) {
    board[i] |= hiddenBit(); // compares all of the two bits between board and
                             // hidden bit, turns the fifth bit to 1, or hidden
  }
}
void cleanBoard(char *board) {
  delete[] board;
  board = nullptr;
}

void printBoard(char *board, std::size_t xdim, std::size_t ydim) {
  int counter = 0;
  for (int i = 0; i < ydim; i++) {   // loops through the number of rows
    for (int j = 0; j < xdim; j++) { // loops through the number of columns
      if ((board[i * xdim + j] & markedBit()) == 
          markedBit()) { // or operator //mistakes: if board[i] & marked bit
                         // == 1.. when you or operator equal one, it doesn't 1
                         // because computer returns hexadecimal. so does not
                         // return one
        std::cout << 'M';
      } else if ((board[i * xdim + j] & hiddenBit()) ==
                 hiddenBit()) { // if xdim times y location + x location
        std::cout << '*';
      } else {
        std::cout << (int)board[i * xdim +
                                j]; // this case the marked bit and hidden bit
                                    // are both 0. so you             only need
                                    // to convert the first four bit to integers
      }
    }
    std::cout << std::endl;
  }
}
// x or thr mark bit when u find the location
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc,
         std::size_t yloc) {
  //board[xdim * yloc + xloc] algorithm for finding the index in the line of array
  if ((board[xdim * yloc + xloc] & hiddenBit()) != hiddenBit()) { // hidden bit is 0, so it is revealed by the user
    return 2;// returns 2
  } else {
    board[xdim * yloc + xloc] ^= markedBit(); // this toogles the markedbit function, means on and off
    return 0;
  }
}
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim) {
  // executed when the game is won, this means either a geese is reveraled or
  // all fields are revealed.
  int counter = 0; 
  for(int i=0; i< xdim*ydim; i++){
    if((board[i] & hiddenBit()) !=hiddenBit()){// if it is revealed 
      counter ++; //counter plus one 
    }else if((board[i] & valueMask()) == 9){
      counter ++; 
    }
  }
  return counter == xdim*ydim;
}
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim) {
  for(int i=0; i< ydim; i++){ //y dim gives you row 
    for(int j=0; j< xdim; j++){ //xdim gives you column 
      if((board[(i*xdim)+j] & valueMask()) != 9){
        if((board[(i-1)*xdim+j] & valueMask()) ==9 && i>0){//top
            board[i*xdim+j] +=1;
          }
        if((board[(i+1)*xdim+j] & valueMask()) == 9 && i<ydim-1){//bottom
            board[i*xdim+j] +=1;
          }
        if((board[i*xdim+(j-1)] & valueMask()) == 9 && j>0){ //left
            board[i*xdim+j] +=1;
          }
        if((board[i*xdim+(j+1)] & valueMask()) == 9 && j<xdim-1){ //check right
            board[i*xdim+j] +=1;
          }
        if((board[(i-1)*xdim+(j-1)] & valueMask()) ==9 && i>0 && j>0){/*check top left*/      board[i*xdim+j] +=1;
          }
        if((board[(i-1)*xdim+(j+1)] & valueMask()) ==9 && j<xdim-1 && i>0){//check top right
            board[i*xdim+j] +=1;
          }
        if((board[(i+1)*xdim+(j-1)] & valueMask()) ==9 && j>0 && i<ydim-1){//bottom left check
            board[i*xdim+j] +=1;
          }
        if((board[(i+1)*xdim+(j+1)] & valueMask()) ==9 && j<xdim-1 && i<ydim-1){ //bottom right check
            board[i*xdim+j] +=1;
        }
      }
    }
  }
//   // This function receives a board array with all elements set to the values 0 or 9. The function updates the board array such that all fields that do not have a goose (value 9) have their value set to the number of geese adjacent to that field
}
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    if((board[yloc*xdim+xloc] & markedBit()) == markedBit()){// if the field is marked
      return 1;
    }
    if((board[yloc*xdim+xloc] & hiddenBit()) != hiddenBit()){//if the field is already revealed 
      return 2;//return 2 
    }
    if((board[yloc*xdim+xloc] & valueMask()) == 9){ //Check if there is a goose in the field. This is done by using value mass and operator them. after and operation, if it the rest of the value in hexadecimal is equal to the hexadecmial of 9, then:
      board[yloc*xdim+xloc] &= ~hiddenBit(); //reveal the chosen field 
      return 9;//return 9
    }
      board[yloc*xdim+xloc] &= ~hiddenBit(); // revealing the chosen field 
    if((board[yloc*xdim+xloc] & valueMask()) == 0){ //the chosen field has a value 0, which is empty field. This is done by and operator with value Mask to remove hidden bits and marked bits. 
      //reveal neighboring field of that chosen empty field
      if(yloc>0){ //checks if top is inbound
        board[(yloc-1)*xdim+xloc] &= ~hiddenBit(); 
      }
      if(yloc<ydim-1){ //checks if bottom is inbound
        board[(yloc+1)*xdim+xloc] &= ~hiddenBit(); 
      }
      if(xloc>0){//checs if left is inbound 
        board[yloc*xdim+(xloc-1)] &= ~hiddenBit(); 
      }
      if(xloc<xdim-1){ //checks if right is inbound
        board[yloc*xdim+(xloc)+1] &= ~hiddenBit(); 
      }
      if(xloc>0 && yloc>0){//checks if top left is in bound
        board[(yloc-1)*xdim+(xloc-1)] &= ~hiddenBit(); 
      }
      if(yloc>0 && xloc<xdim-1){//checks if top right is in bound 
        board[(yloc-1)*xdim+(xloc+1)] &= ~hiddenBit(); 
      }
      if(yloc<ydim-1 && xloc>0){//checks if bottom left is in bound 
        board[(yloc+1)*xdim+(xloc-1)] &= ~hiddenBit(); 
      }
      if(yloc<ydim-1 && xloc<xdim-1){//checks if bottom right is in bound 
        board[(yloc+1)*xdim+(xloc+1)] &= ~hiddenBit(); 
      }
    }
    return 0;
  }