//Authors: Liam Hilton & Khoa Minh Do
//Date: 5/7/2024
//Purpose: Final_Project

#include <stdio.h>
#include <stdbool.h>

#define MAX_ROW 30    
#define MAX_COL 30    
#define SIZE 20

//0 = ' ', 1 = '.', 2 = 'o', 3 = 'O', 4 = '0'

void load_image(FILE * fp, char board[MAX_ROW][MAX_COL],int* success, int *c_row, int *c_col);

void display(int row, int col, char symbol_array[MAX_ROW][MAX_COL]); //DISPLAY CURRENT IMAGE

char convert (char num);  //conver number from file to character

void print_array(int row, int col, char array[][col] );

int edit_menu(int *choice);

void dim (int row, int col, char symbol_array[MAX_ROW][MAX_COL] );

void brightn(int row, int col, char symbol_array[MAX_ROW][MAX_COL] );

void crop(int row, int col,char symbol_array[MAX_ROW][MAX_COL]);

void saveI(int row, int col, char array[][col]);

char re_convert (char num);
//FUNCTION SUPPORT CROP FUNCTION
void transfer(int row, int col, char symbol_array[][col], char tran_arr[MAX_ROW][MAX_COL]);
void display_convert(int row, int col, char symbol_array[][col], char tran_arr[MAX_ROW][MAX_COL]);


int main(){
	int choice, edit_choice;
	char draw[MAX_ROW][MAX_COL];
	char filename[SIZE];
	int check = 0;
	int Row=0,Col=0;
	
	
	do{
		printf("**ERINSTAGRAM**\n");
		printf("1: Load image\n");
		printf("2: Display image\n");
		printf("3: Edit image\n");
		printf("0: EXIT\n\n");
		printf("Choose from one of the options above: ");
		scanf("%d", &choice);
		printf("\n");
		
		switch(choice){
			case 1:
				printf("What is the name of the image file? ");
				scanf("%s", filename);
				
				FILE*fp;
					fp = fopen(filename, "r");
					load_image(fp,draw, &check, &Row, &Col);
					//printf("test in main\n");
				if(check==1){
					fclose(fp);
				}	
				
				break;
			case 2:	
				display(Row,Col, draw);
				break;
			case 3: 
				
				edit_menu(&edit_choice);
				
				switch(edit_choice){
					case 1: //crop
						crop(Row,Col, draw);
						for (int i = 0; i < Row; i++) {
							for (int j = 0; j < Col; j++){
				  				draw[i][j]=re_convert(draw[i][j]);
							}
						}
						break;
					break;
					case 2: //DIM
						dim(Row,Col, draw);
						break;
					case 3: //Brighten
						brightn(Row,Col, draw);
						break;
					case 0:
						break;
					default:
						printf("Invalid option, please try agian.\n");
						break;
					}
				break;
			case 0:
				printf("\nGoodbye!\n\n");
				return 0;
				break;
			default:
				printf("Invalid option, please try agian.\n");
				break;
	} 
		}while(choice != 0);
	
	return 0;
}

void saveI(int row, int col, char array[][col]){
	char choice;
	char file_name[SIZE];
	
	printf("Would you like to save the file? (y/n) ");
	scanf(" %c", &choice);
	
	if(choice == 'y'){
		printf("what do you want to name the image file? (include the extension) ");
		scanf("%s", file_name);
		
		char copy_arr[row][col];
		
		
		
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++){
				copy_arr[i][j] = array[i][j];
				copy_arr[i][j] = re_convert(copy_arr[i][j]); 
			}
		}
		
		
		/*printf("\nTEST\n");
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++){
				printf("%c", copy_arr[i][j]);
			}
		}
		*/
		FILE *fptr;
		fptr = fopen(file_name,"w");
		
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++){
			fprintf(fptr, "%c", copy_arr[i][j]);  
		}
			if(i != row-1){
				fprintf(fptr ,"%c", '\n');
			}
		} 
		fclose(fptr);
		printf("\nImage successfully saved!\n");
		}
		
	}

void load_image(FILE * fp, char board[MAX_ROW][MAX_COL],int* success, int *c_row, int *c_col){
	int indexR=0,indexC=0;
	int Max=30;
	char line[Max];
	int lineLength=0;
	bool done=true;
	
	
	if(fp == NULL){
		printf("Could not find an image with that filename.\n");
		*success=0;
	}
	else if(fp != NULL){			
	 	/*for (int i = 0; i < MAX_ROW; i++) {
	 		*c_row = i;
			for (int j = 0; j < MAX_COL; j++){
				fscanf(fp, " %c", &board[i][j]);
				*c_col=j;  
			}
			
		}
		*/
		while(fscanf(fp,"%c",&board[indexR][indexC])==1){
			
			if(board[indexR][indexC]=='\n'){
			//printf("Row:%d\n",indexR);
			indexR++;
			indexC=0;
			
			}
			else{
			//printf("Col: %d\n",indexC);
			//indexR=0;
			indexC++;
			*c_col=indexC;
			}
			
			
		}
		
		*c_row=indexR+1;
		printf("\n\nImage successfully loaded!\n\n");
		//printf("test\n");
		*success=1;
		
		
		/*do{
			//printf("test in loop\n");
			//fgets(line,Max,fp);
			lineLength=0;
			while (line[lineLength] != '\0'){
				lineLength++;
			}
			if(*c_col <= lineLength){
			printf("test in if statemnet1\n");
				*c_col=lineLength;
			}
			if(line[lineLength] == '\0'){
			printf("test in if statemnet2\n");
				done = false;
			}
			*c_row++;
		
		}while(done);*/
		//*c_row = index;
		//printf("\nNum of row %d\n", *c_row);
		//printf("Num of col %d\n\n", *c_col);
		
	}
}


//CONVERT
char convert (char num){
	switch(num) {
        case '0':
            return ' ';
        case '1':
            return '.';
        case '2':
            return 'o';
        case '3':
            return 'O';
        case '4':
            return '0';
        default: // test
            return 'X';
    }
}

//re_convert
char re_convert (char num){
	switch(num) {
        case ' ':
            return '0';
        case '.':
            return '1';
        case 'o':
            return '2';
        case 'O':
            return '3';
        case '0':
            return '4';
        default: // test
            return 'X';
    }
}
void print_array(int row, int col, char array[][col] ){
		
	
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
		
		printf("%c", array[i][j]);
		}
		printf("%c", '\n');
	}
	printf("\n");
}


    
void display(int row, int col, char symbol_array[MAX_ROW][MAX_COL]) {
    //printf("\nNum of row %d\n", row);
		//printf("Num of col %d\n\n", col);
    char convert_array[row][col];
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            convert_array[i][j] = symbol_array[i][j]; // Copy from symbol_array
            convert_array[i][j] = convert(convert_array[i][j]);
        }
    }
    //printf("\nNum of row %d\n", row);
		//printf("Num of col %d\n\n", col);
    print_array(row,col, convert_array); // Print the copied array
}
int edit_menu(int *choice){
	printf("\n\n**EDITING**\n");
	printf("1: Crop image\n");
	printf("2: Dim image\n");
	printf("3: Brighten image\n");
	printf("0: Return to main menu\n\n");
	printf("Choose from one of the options above: ");
	scanf("%d", choice);
	
	
	return *choice;
}
void transfer(int row, int col, char symbol_array[][col], char tran_arr[MAX_ROW][MAX_COL]){  //this function used to add small array intio big array.
    

    
    for(int i = 0; i < MAX_ROW; i++){
        for(int j = 0; j < MAX_COL; j++){
            tran_arr[i+1][j+1] = symbol_array[i][j];
        }
    }
    for(int j = 0; j < MAX_COL; j++){
        tran_arr[0][j] = '0';
        
    } 
    for(int i = row + 1; i < MAX_ROW; i++ ){
        for(int j = 0; j < MAX_COL; j++){
        tran_arr[13][j] = '0';
        }
    }
    for(int i = 0; i < MAX_ROW; i++){
        tran_arr[i][0] = '0';
    }
    
      // Display '1' at [0][1] and [1][0]
    tran_arr[0][1] = '1';
    tran_arr[1][0] = '1';
    tran_arr[0][20] = '2';
    tran_arr[0][21] = '1';
    tran_arr[13][0] = '1';
    tran_arr[13][1] = '2';
    
}
void display_convert(int row, int col, char symbol_array[][col], char tran_arr[MAX_ROW][MAX_COL]){//convert the the tran_arr to symbol
        
        
        for (int i = 0; i <= row; i++){
        for(int j = 0; j <= col; j++){
        
            tran_arr[i][j] = convert(tran_arr[i][j]);
        }
    }
        
        printf("\n 1");
    	for(int i=0; i < col; i++){
    		printf(" ");
    	}
    	printf("%d\n",col);
    	printf("1");	
     	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
		
		printf("%c", tran_arr[i][j]);
		}
		printf("%c", '\n');
		if(i<row){
		printf(" ");
		}
	}
	printf("%d\n",row);
        
        
        
        // The parameter in here for BIG 2D ARRAY
        /*char convert_array[MAX_ROW][MAX_COL];
        printf("yay");
        transfer(row, col,symbol_array,tran_arr);
        
        for (int i = 0; i < MAX_ROW; i++) {
            for (int j = 0; j < MAX_COL; j++) {
            convert_array[i][j] = tran_arr[i][j]; // Copy from symbol_array
            if(i == 0 && j == 1 ||i == 1 && j == 0 ||i == 0 && j == 20 ||i == 0 && j == 21 ||i == 13 && j == 0 ||i == 13 && j == 1 ){
              convert_array[i][j] =  convert_array[i][j];
            }else{
            convert_array[i][j] = convert(convert_array[i][j]);
            }
        }
    }
    
     for(int i = 0; i < MAX_ROW; i++){
		for(int j = 0; j < MAX_COL; j++){
		
		printf("%c", convert_array[i][j]);
		}
		printf("%c", '\n');
	} // Print the copied array
	*/
}


void crop(int row, int col,char symbol_array[MAX_ROW][MAX_COL]){
    
    int left, right_left, top, bottom;
    char array[row][col];
    
    char cop_array[MAX_ROW][MAX_COL];

    display_convert(row, col,array, symbol_array);
    
    
    printf("This image you want to crop is %d x %d.\n",row,col);
    printf("The Row and column values start in upper lefthand corner.\n");
    //LEFT
    do{
        printf("\nWhich column do you want to be the new left side? ");
        scanf("%d", &left);
        if (left < 0 || left >= col-1){
            printf("Invalid column value. Choose a value between 0 and 21: ");
            scanf("%d", &left);
        } 
    }while(left < 0 || left >= col-1);
    //RIGHT_LEFT
    do{
        printf("\nWhich column do you want to be the right left side? ");
        scanf("%d", &right_left);
        if (right_left < left || right_left > col -1){
            printf("Invalid column value. Choose a value between %d and 20: ", left);
            scanf("%d", &right_left);
        } 
    }while(right_left < left || right_left > col - 1);
    //TOP
   do{
        printf("\nWhich row do you want to be the new top? ");
        scanf("%d", &top);
        if (top < 0 || top > row ){
            printf("Invalid column value. Choose a value between 0 and 11: ");
            scanf("%d", &top);
            
        } 
    }while(top < 0 || top > row );
    //bottom
    do{
        printf("\nWhich row do you want to be the new bottom? ");
        scanf("%d", &bottom);
        if (bottom < top || bottom > row ){
            printf("Invalid column value. Choose a value between %d and 11: ", top);
            scanf("%d", &bottom);
            
        } 
    }while(bottom < top || bottom > row);
    
    //Display cropped
    printf("\n");
    
    //COPY array
    for (int a = 0; a < row; a++) {
        for (int b = 0; b < col; b++) {
            cop_array[a][b] = symbol_array[a][b]; // Copy from symbol_array
        }
    }
    
    /*for (int i = 0; i <= bottom-1; i++){
        for(int j = 0; j <= right_left - 1; j++){
        
            cop_array[i][j] = symbol_array[(top-1)+i][(left-1)+j];
            //printf("%c", symbol_array[i][j]);  //cop_array
        }
        
    printf("\n");
    }
    */
    //printf("\n");
    int new_row = (bottom - top)+1;
    int new_col = (right_left - left)+1;
    
    //printf("New Row: %d\n",new_row );
    //printf("New Col: %d\n",new_col );
    
    
    //printf("\n");
    
    for (int a = 0; a < new_row; a++) {
        		for (int b = 0; b < new_col; b++) {
            			printf("%c",cop_array[a][b]);
        		}
       	 		printf("\n");
    	}
    	
    //save function
    	char choice;
	char file_name[SIZE];
	
	printf("Would you like to save the file? (y/n) ");
	scanf(" %c", &choice);
	printf("\n");
	
	if(choice == 'y'){
		printf("what do you want to name the image file? (include the extension) ");
		scanf("%s", file_name);
		
		char copy_arr[new_row][new_col];
		
		
		
		for (int i = 0; i < new_row; i++) {
			for (int j = 0; j < new_col; j++){
				copy_arr[i][j] = cop_array[i][j];
				copy_arr[i][j] = re_convert(copy_arr[i][j]); 
			}
		}
		
		
		/*printf("\nTEST\n");
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++){
				printf("%c", copy_arr[i][j]);
			}
		}
		*/
		FILE *fptr;
		fptr = fopen(file_name,"w");
		
		for (int i = 0; i < new_row; i++) {
			for (int j = 0; j < new_col; j++){
			fprintf(fptr, "%c", copy_arr[i][j]);  
		}
			if(i != row-1){
				fprintf(fptr ,"%c", '\n');
			}
		} 

		fclose(fptr);
		printf("\nImage successfully saved!\n");
		}
		else{
		printf("\n");
		}
		
		
}

void dim (int row, int col, char symbol_array[MAX_ROW][MAX_COL] ) {
 	
 	char dim_array[row][col];
 	
 	for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if(symbol_array[i][j] == '0'){
                dim_array[i][j] = symbol_array[i][j];
            } else if(symbol_array[i][j] != '0'){
                dim_array[i][j] = symbol_array[i][j] - 1;
                
            }
             dim_array[i][j] = convert(dim_array[i][j]);
 
        }
 }
  print_array(row,col, dim_array);
  saveI(row, col, dim_array);
}
void brightn(int row, int col, char symbol_array[MAX_ROW][MAX_COL]){
 	char bri_array[row][col];
 	
 	for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if(symbol_array[i][j] == '4'){
                bri_array[i][j] = symbol_array[i][j];
            } else if(symbol_array[i][j] != '4'){
                bri_array[i][j] = symbol_array[i][j] + 1;
                
            }
             bri_array[i][j] = convert(bri_array[i][j]);
 
        }
 }
  print_array(row,col, bri_array);
  
  saveI(row,col, bri_array);
}
    
