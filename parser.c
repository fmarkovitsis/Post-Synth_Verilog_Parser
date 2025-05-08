#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 30000
#define HASH_D_SIZE 20


// struct for parsing the elements in the assign statement // 
// it is called each time in both elements and keep the infos for the other element//
typedef struct 
{
  unsigned long connection_hash;
  int connection_depth;
  int connection_type; // 0 to search in ios array , 1 to search in wires array //
}assign_connections;


// struct with the infos of the wires //
typedef struct 
{
  int valid_element;  // it shows that the position of the array is filled with element//
  char *name;
  int **component_array_position; // the pos (h,d) of the component in the component_array whose pin is connected with this wire//
  int num_of_ccs;
  assign_connections *assign_connections_array; // the connections of the wire with other wires or ios //
  int num_of_assign_connections;
  int is_constant; // if assign case gives value 1'b0 -> 0 or 1'b1 ->1 to the element else -1//  
} wire;
 
typedef struct 
{
  wire **wire_array;
  unsigned long number_of_wires;
} wires_hash;


// struct with the infos of the primary IOs //
typedef struct
{
  int valid_element;
  char *name;
  int in_out_io; // 0 for input, 1 for output //
  int **component_array_position; // the pos (h,d) of the component in the component_array whose pin is connected with this io//
  int num_of_ccs;
  assign_connections *assign_connections_array; // the connections of the io with other io/wires //
  int num_of_assign_connections; 
  int is_constant; // if assign case gives value 1'b0 -> 0 or 1'b1 ->1 to the element else -1//
} primary_io;

typedef struct
{
  primary_io **primary_io_array;
  unsigned long number_of_ios;
} primary_ios_hash;


// struct with the infos of general gates //
// always the output(or 2 outputs for dff ) is in the last thesis //
typedef struct
{
  char *name;
  unsigned num_pins;
  char **pin_names; // general pin names //
} gate;


// struct with the infos of the components //
typedef struct
{
  int valid_element;
  char *name;
  int gate_type_pos;  // find the general gate type for the specific component //

  // keep position(h,d) of the wires/ios which are connected to the components general pins//
  int **wire_pins;  
  int **io_pins;
} component;

typedef struct
{
  unsigned long num_components;
  component **component_array;
} component_hash;

primary_ios_hash *ios_array;
wires_hash *wires_array;
component_hash *components_array;

gate *gates_array;
unsigned gates_array_size = 0;


// function that take this word for example .A1(n7150) and return A1(gate pin name) // 
char *create_gate_pin_name(const char *word) 
{
  size_t new_name_length;
  char *new_name;
  const char *parenthesis_position;
  
  parenthesis_position = strchr(word, '(');
  if (parenthesis_position == NULL) 
    {
      fprintf(stderr, "Invalid format: missing '(' in create_gate_pin_name\n");
      return NULL;
    }

  // Calculate the length of name (excluding the dot and '(') //
  new_name_length = parenthesis_position - word - 1;

  // memory for the new string //
  new_name = (char *)malloc(new_name_length + 1); // +1 for null terminator //
  if (new_name == NULL) 
    {
      perror("Memory allocation failed in create_gate_pin_name");
      return NULL;
    }

  // Copy new_name into the new string
  strncpy(new_name, word + 1, new_name_length); // Skip the leading dot //
  new_name[new_name_length] = '\0'; // Null-terminate the string //


  return new_name;
}


// function for malloc new strings //
char *strdup(const char *str) 
{
  size_t len;
  char *copy;

  len = strlen(str) + 1; // Include space for the null terminator //
  copy = malloc(len);
  if (copy) 
    {
      memcpy(copy, str, len); // Copy the string, including the null terminator//
    }
  return copy;
}

// function to create a gate named DFF_X1 and put the 4 pins: D, CK, Q, QN //
void create_dff (FILE *file) 
{
  char *word;
  char line[MAX_LINE_LENGTH];

  //always keep one extra position
  gates_array[gates_array_size - 1].pin_names = (char **)malloc(sizeof(char *) * 5); //one extra like the others //
  if (gates_array[gates_array_size - 1].pin_names == NULL) 
    {
      fprintf(stderr, "Memory allocation failed for gates_array[%d].pin_names\n", gates_array_size - 1);
      exit(1);
    }

  gates_array[gates_array_size - 1].num_pins = 4;

  gates_array[gates_array_size - 1].pin_names[0] = strdup("D");
  gates_array[gates_array_size - 1].pin_names[1] = strdup("CK");
  gates_array[gates_array_size - 1].pin_names[2] = strdup("Q");
  gates_array[gates_array_size - 1].pin_names[3] = strdup("QN");


  word = strtok(NULL, " \t\n\r"); // Read the name of the 1st pin of the Component//

  // while ( strcmp(word, ");" ) !=0)
  while (1)
    {
      if (word == NULL ) // No more words to read
        {
          fgets(line, sizeof(line), file); // Read the next line
          line[strcspn(line, "\n")] = '\0';
          word = strtok(line, " \t\n\r");
          continue; 
        }

      if (word[strlen(word) - 1] == ';')
        {
          break;
        }
      
      word = strtok(NULL, " \t\n\r"); // Read the name of the next pin of the Component//
    }
} 

// Function for the 1st parsing in order to find the number of elements //
// and initialize gate array//
void parsing_number_of_elements(FILE *file)
{
  gate *temp;
  char **temp_pin;
  char line[MAX_LINE_LENGTH];
  char *word;
  int i;
  int gate_exists = 0;
  char *gate_pin_name;

  printf("1st Parsing in order to find the number of elements...\n");

  while ( fgets(line, sizeof(line), file) )   // Read each line 
    {
      line[strcspn(line, "\n")] = '\0';       // Remove newline character at the end of the line, if any //
      word = strtok(line, " \t\n\r");               // Split the line into words //

      if(word == NULL)                        //empty line
        {
          continue;
        }
      else if (word[0] == '/' && word[1] == '/')
        {
          continue; // Skip comment lines
        }
      else if (strcmp(word, "assign") == 0)
        {
          continue;
        }
      else if ((strcmp(word, "input") == 0) || (strcmp(word, "output") == 0))
        {
          word = strtok(NULL, " \t\n\r");
          while (1)
            {
              if (word == NULL ) // No more words to read
                {
                  fgets(line, sizeof(line), file); // Read the next line
                  line[strcspn(line, "\n")] = '\0';
                  word = strtok(line, " \t\n\r"); 
                  continue; 
                }

              if (word[strlen(word) - 1] == ';')
                {
                  break;
                }
                  
              word = strtok(NULL, " \t\n\r");
            }
        }
      else if (strcmp(word, "module") == 0)
        {
          word = strtok(NULL, " \t\n\r"); //name of the module//
          word = strtok(NULL, " \t\n\r"); // ( //

          word = strtok(NULL, " \t\n\r"); // first io //

          while (1)
            { 
              if (word == NULL ) // read next line of the file //
                {
                  fgets(line, sizeof(line), file); // Read the next line
                  line[strcspn(line, "\n")] = '\0'; 
                  word = strtok(line, " \t\n\r"); 
                  continue; 
                }

              if (word[0] == ')')
                {
                  break;
                }
              // printf("first parsing ... read io: %s\n", word);
              ios_array->number_of_ios++;
                  
              word = strtok(NULL, " \t\n\r");
            }

          printf("\nfirst parsing ... number of ios: %lu\n\n", ios_array->number_of_ios);
        }
      else if (strcmp(word, "wire") == 0)
        {
          word = strtok(NULL, " \t\n\r"); // Read the name of the 1st wire //

          while (1)
            {
              if (word == NULL ) // No more words to read
                {
                  fgets(line, sizeof(line), file); // Read the next line
                  line[strcspn(line, "\n")] = '\0';
                  word = strtok(line, " \t\n\r"); 
                  continue; 
                }

              if (word[strlen(word) - 1] == ';')
                {
                  // printf("first parsing ... read wires: %s\n", word);
                  wires_array->number_of_wires++;
                  break;
                }
              // printf("first parsing ... read wires: %s\n", word);
              wires_array->number_of_wires++;
                  
              word = strtok(NULL, " \t\n\r");
            }

          printf("\nfirst parsing ... number of wires: %lu\n\n", wires_array->number_of_wires);
        } 
      else if (strcmp(word, "endmodule") == 0)
        {
          break; // End of the module
        }
      else 
        {
          //read gates infos and create gate array
          
          //for sentence to begin with ); or ;
          if (word[strlen(word) - 1] == ';')
            {
              continue;
            }

          gate_exists = 0;

          for (i=0; i<gates_array_size; i++)
            {
              if (strcmp(word, gates_array[i].name) == 0)
                {
                  gate_exists = 1;
                  components_array->num_components++;
                  break;
                }
            }

          if (gate_exists == 0) // it doesnt exist so add the gate (lib)
           {

            if (isalpha(word[0]) && (word[strlen(word) -1] != ')'))
              {
                gates_array[gates_array_size].name = strdup(word);
                gates_array[gates_array_size].num_pins = 0;
                gates_array[gates_array_size].pin_names = NULL;
                gates_array_size++; 
              }
            else 
              {
                continue;
              }

              components_array->num_components++;


              //always keep one extra position
              temp = (gate *)realloc(gates_array, sizeof(gate) * (gates_array_size + 1));
              if (temp == NULL) 
                {
                  fprintf(stderr, "Memory allocation failed for gates_array\n");
                  exit(1);
                }
              
              gates_array = temp;
              
              if (strcmp(word, "DFF_X1") == 0)
                {
                  create_dff(file);
                  continue;
                }

              // create the gate_pin_infos
              gates_array[gates_array_size - 1].pin_names = (char **)malloc(sizeof(char *));
              if (gates_array[gates_array_size - 1].pin_names == NULL) 
                {
                  fprintf(stderr, "Memory allocation failed for gates_array[%d].pin_names\n", gates_array_size - 1);
                  exit(1);
                }
              
            
              word = strtok(NULL, " \t\n\r"); // Read the name of the Component //
              word = strtok(NULL, " \t\n\r"); // Read "(" //
              word = strtok(NULL, " \t\n\r"); // Read the name of the 1st pin of the Component//


              // while ( strcmp(word, ");" ) !=0)
              while (1)
                {
                  if (word == NULL ) // No more words to read
                    {
                      fgets(line, sizeof(line), file); // Read the next line
                      line[strcspn(line, "\n")] = '\0';
                      word = strtok(line, " \t\n\r"); 
                      continue; 
                    }

                  if (word[strlen(word) - 1] == ';')
                    {
                      break;
                    }

                  
                    //store general pin names
                  
                  gate_pin_name = create_gate_pin_name(word);
                  gates_array[gates_array_size - 1].pin_names[gates_array[gates_array_size - 1].num_pins] = gate_pin_name;
                  gates_array[gates_array_size - 1].num_pins++;

                  temp_pin = (char **)realloc(gates_array[gates_array_size - 1].pin_names, sizeof(char*)*(gates_array[gates_array_size - 1].num_pins + 1));
                  if (temp_pin == NULL)
                    {
                      fprintf(stderr, "Memory allocation failed for temp_pin");
                      exit(1);
                    }
                  
                  gates_array[gates_array_size - 1].pin_names = temp_pin;
                  word = strtok(NULL, " \t\n\r");
                }
            }
        }

      word = NULL;
    }

}


// Hash function to convert a string to an unsigned long integer //
// The hash value is computed by iterating over each character in the string and updating the hash value accordingly //
// The final hash value is returned as an unsigned long integer //
unsigned long hash_function(char *str)
{
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}


// function to insert the element in the proper io/wire array//
void insert_io_wire(int type, char* element_name)
{
  unsigned long hash_position;
  int i;
  char *name = NULL;

  element_name[strlen(element_name)-1] = '\0'; //remove , from the word//
  name = strdup(element_name);
   
  if(type == 0)//input 
    {
      hash_position = hash_function(name) % (ios_array->number_of_ios);
      for(i=0; i < HASH_D_SIZE; i++)
        {
          if(ios_array->primary_io_array[hash_position][i].valid_element == 0)
            {
              ios_array->primary_io_array[hash_position][i].valid_element = 1;
              ios_array->primary_io_array[hash_position][i].name = name;
              ios_array->primary_io_array[hash_position][i].in_out_io = 0;
              ios_array->primary_io_array[hash_position][i].is_constant = -1; // -1 means not constant //

              ios_array->primary_io_array[hash_position][i].component_array_position = (int **)malloc(sizeof(int*));
              if (ios_array->primary_io_array[hash_position][i].component_array_position == NULL) 
                {
                  fprintf(stderr, "Memory allocation failed for ios_array[%lu][%d].component_array_position\n", hash_position, i);
                  exit(1);
                }
              ios_array->primary_io_array[hash_position][i].component_array_position[0] = (int *)malloc(sizeof(int) * 2);
              if (ios_array->primary_io_array[hash_position][i].component_array_position[0] == NULL) 
                {
                fprintf(stderr, "Memory allocation failed for ios_array[%lu][%d].component_array_position[0]\n", hash_position, i);
                exit(1);
              }

              ios_array->primary_io_array[hash_position][i].num_of_ccs = 0;

              ios_array->primary_io_array[hash_position][i].num_of_assign_connections = 0;


              // printf("insert_io_wire input ok\n");
              break;
            }
        }
    }
  else if(type == 1)//output
    {
      hash_position = hash_function(name) % (ios_array->number_of_ios);
      for(i=0; i < HASH_D_SIZE; i++)
        {
          if(ios_array->primary_io_array[hash_position][i].valid_element == 0)
            {
              ios_array->primary_io_array[hash_position][i].valid_element = 1;
              ios_array->primary_io_array[hash_position][i].name = name;
              ios_array->primary_io_array[hash_position][i].in_out_io = 1;
              ios_array->primary_io_array[hash_position][i].is_constant = -1; // -1 means not constant //

              ios_array->primary_io_array[hash_position][i].component_array_position = (int **)malloc(sizeof(int*));
              if (ios_array->primary_io_array[hash_position][i].component_array_position == NULL) 
                {
                  fprintf(stderr, "Memory allocation failed for ios_array[%lu][%d].component_array_position\n", hash_position, i);
                  exit(1);
                }

              ios_array->primary_io_array[hash_position][i].component_array_position[0] = (int *)malloc(sizeof(int) * 2);
              if (ios_array->primary_io_array[hash_position][i].component_array_position[0] == NULL) 
                {
                  fprintf(stderr, "Memory allocation failed for ios_array[%lu][%d].component_array_position[0]\n", hash_position, i);
                  exit(1);
                }


              ios_array->primary_io_array[hash_position][i].num_of_ccs = 0;
              ios_array->primary_io_array[hash_position][i].num_of_assign_connections = 0;
        
              // printf("insert_io_wire output ok\n");
              break;
            }
        }
    }
  else//wire  
    {
      hash_position = hash_function(name) % (wires_array->number_of_wires );
      for(i=0; i < HASH_D_SIZE; i++)
        {
          if( wires_array->wire_array[hash_position][i].valid_element == 0)
            {
              wires_array->wire_array[hash_position][i].valid_element = 1;
              wires_array->wire_array[hash_position][i].name = name;
              wires_array->wire_array[hash_position][i].is_constant = -1; // -1 means not constant //

              wires_array->wire_array[hash_position][i].component_array_position = (int **)malloc(sizeof(int*));
              if ( wires_array->wire_array[hash_position][i].component_array_position == NULL) 
                {
                  fprintf(stderr, "Memory allocation failed for wires_array[%lu][%d].component_array_position\n", hash_position, i);
                  exit(1);
                }

              wires_array->wire_array[hash_position][i].component_array_position[0] = (int *)malloc(sizeof(int) * 2);
              if ( wires_array->wire_array[hash_position][i].component_array_position[0] == NULL) 
                {
                  fprintf(stderr, "Memory allocation failed for wires_array[%lu][%d].component_array_position[0]\n", hash_position, i);
                  exit(1);
                }

              wires_array->wire_array[hash_position][i].num_of_ccs = 0;
              wires_array->wire_array[hash_position][i].num_of_assign_connections = 0;

              // printf("insert_io_wire wire ok\n");
              break;
            }
        }
    }
}


// function that finds the gate type of a component//
int find_gate_type(char* element_name)
{
  int i;

  for(i=0; i < gates_array_size; i++)
    {
      if(strcmp(gates_array[i].name, element_name) == 0)
        {
          return i;
        }
    }
  return -1;
}


// function that takes the word for example .A1(n7150) and returns n7150 (component name) //
char *keep_pins_special_name(const char *word) 
{
  const char *open_parenthesis;
  const char *close_parenthesis;
  size_t pin_name_length;
  char *pin_name;

  // Find the position of the opening '('
  open_parenthesis = strchr(word, '(');
  if (open_parenthesis == NULL) 
    {
      fprintf(stderr, "Invalid format: missing '('\n");
      return NULL;
    }

  // Find the position of the closing ')'
  close_parenthesis = strchr(open_parenthesis, ')');
  if (close_parenthesis == NULL) 
    {
      fprintf(stderr, "Invalid format: missing ')'\n");
      return NULL;
    }

  // Calculate the length of name
  pin_name_length = close_parenthesis - open_parenthesis - 1;

  // Allocate memory for the new string
  pin_name = (char *)malloc(pin_name_length + 1); // +1 for null terminator
  if (pin_name == NULL) 
    {
      perror("Memory allocation failed");
      return NULL;
    }

  // Copy pin_name into the new string
  strncpy(pin_name, open_parenthesis + 1, pin_name_length); // Skip the '('
  pin_name[pin_name_length] = '\0'; // Null-terminate the string

  return pin_name;
}



// function that connects the component pins with the ios/wires //
void connect_ccs_to_wires_ios(int comp_hash, int comp_depth, int is_io_or_wire, int io_or_wire_depth, unsigned long io_or_wire_hash)
{
  int num_of_ccs;

  if(is_io_or_wire == 0)//io
    {
      num_of_ccs = ios_array->primary_io_array[io_or_wire_hash][io_or_wire_depth].num_of_ccs;
      ios_array->primary_io_array[io_or_wire_hash][io_or_wire_depth].component_array_position[num_of_ccs][0] = comp_hash;
      ios_array->primary_io_array[io_or_wire_hash][io_or_wire_depth].component_array_position[num_of_ccs][1] = comp_depth;

      ios_array->primary_io_array[io_or_wire_hash][io_or_wire_depth].num_of_ccs++;
      ios_array->primary_io_array[io_or_wire_hash][io_or_wire_depth].component_array_position = (int **)realloc(ios_array->primary_io_array[io_or_wire_hash][io_or_wire_depth].component_array_position, sizeof(int*) * (num_of_ccs + 2));
      if (ios_array->primary_io_array[io_or_wire_hash][io_or_wire_depth].component_array_position == NULL) 
        {
          fprintf(stderr, "Memory allocation failed for ios_array[%lu][%d].component_array_position\n", io_or_wire_hash, io_or_wire_depth);
          exit(1);
        }
      ios_array->primary_io_array[io_or_wire_hash][io_or_wire_depth].component_array_position[num_of_ccs + 1] = (int *)malloc(sizeof(int) * 2);
      if (ios_array->primary_io_array[io_or_wire_hash][io_or_wire_depth].component_array_position[num_of_ccs + 1] == NULL) 
        {
          fprintf(stderr, "Memory allocation failed for ios_array[%lu][%d].component_array_position[%d]\n", io_or_wire_hash, io_or_wire_depth, num_of_ccs + 1);
          exit(1);
        }
    }
  else//wire
    {
      num_of_ccs = wires_array->wire_array[io_or_wire_hash][io_or_wire_depth].num_of_ccs;
      wires_array->wire_array[io_or_wire_hash][io_or_wire_depth].component_array_position[num_of_ccs][0] = comp_hash;
      wires_array->wire_array[io_or_wire_hash][io_or_wire_depth].component_array_position[num_of_ccs][1] = comp_depth;

      wires_array->wire_array[io_or_wire_hash][io_or_wire_depth].num_of_ccs++;
      wires_array->wire_array[io_or_wire_hash][io_or_wire_depth].component_array_position = (int **)realloc(wires_array->wire_array[io_or_wire_hash][io_or_wire_depth].component_array_position, sizeof(int*) * (num_of_ccs + 2));
      if (wires_array->wire_array[io_or_wire_hash][io_or_wire_depth].component_array_position == NULL) 
        {
          fprintf(stderr, "Memory allocation failed for wires_array[%lu][%d].component_array_position\n", io_or_wire_hash, io_or_wire_depth);
          exit(1);
        }

      wires_array->wire_array[io_or_wire_hash][io_or_wire_depth].component_array_position[num_of_ccs + 1] = (int *)malloc(sizeof(int) * 2);
      if (wires_array->wire_array[io_or_wire_hash][io_or_wire_depth].component_array_position[num_of_ccs + 1] == NULL) 
        {
          fprintf(stderr, "Memory allocation failed for wires_array[%lu][%d].component_array_position[%d]\n", io_or_wire_hash, io_or_wire_depth, num_of_ccs + 1);
          exit(1);
        }
    }
}





// function that stores the pins info of a component dff_x1 type//
void dff_pins(FILE *file, unsigned long comp_hash_position, int comp_depth)
{
  char *word;
  char line[MAX_LINE_LENGTH];
  char *gate_pin_name;
  char *component_pin_name;

  unsigned long io_array_position;
  unsigned long wires_array_position;
  // int found_io = 0;

  int j;

  word = strtok(NULL, " \t\n\r"); // Read the name of the 1st pin of the Component//
  
  while(1)
    {          
      if (word == NULL ) // No more words to read
        {
          fgets(line, sizeof(line), file); // Read the next line
          line[strcspn(line, "\n")] = '\0';
          word = strtok(line, " \t\n\r"); 
          continue; 
        }

      if (word[strlen(word) - 1] == ';')
        {
          break;
        }
      
      // printf("dffpins %s\n", word);
      if(word[0] == '.')
        {
          gate_pin_name = create_gate_pin_name(word);

          
          if(word[strlen(word)-1] == '(' )
            {
              fgets(line, sizeof(line), file); // Read the next line
              line[strcspn(line, "\n")] = '\0';
              word = strtok(line, " \t\n\r");

              while(word == NULL)
                {
                  fgets(line, sizeof(line), file); // Read the next line
                  line[strcspn(line, "\n")] = '\0';
                  word = strtok(line, " \t\n\r");
                }

              // remove ) from the word //
              // printf("Component pin name is %s\n", word);

              word[strlen(word)-1] = '\0'; //remove ) from the word//
              component_pin_name = strdup(word); 
              printf("Component pin name  is %s\n", component_pin_name);
            }
          else 
            {
              component_pin_name = keep_pins_special_name(word);
              // printf("Component pin name after is %s\n", component_pin_name);
            }



          if(strcmp(component_pin_name, "1'b0") == 0 )  // if (h,d)=(-4 , -4)->0
            {
              if (strcmp(gate_pin_name, "D") == 0) 
                {
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[0][0] = -4;
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[0][1] = -4;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[0][0] = -4;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[0][1] = -4;
                }
              else if (strcmp(gate_pin_name, "CK") == 0) 
                {
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[1][0] = -4;
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[1][1] = -4;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[1][0] = -4;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[1][1] = -4;
                }
              else if (strcmp(gate_pin_name, "Q") == 0) 
                {
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[2][0] = -4;
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[2][1] = -4;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[2][0] = -4;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[2][1] = -4;
                }
              else if (strcmp(gate_pin_name, "QN") == 0) 
                {
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[3][0] = -4;
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[3][1] = -4;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[3][0] = -4;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[3][1] = -4;
                }

              free(gate_pin_name);
              free(component_pin_name);
              component_pin_name = NULL;
              word = strtok(NULL, " \t\n\r");
              continue;
            }
          if(strcmp(component_pin_name, "1'b1") == 0 ) //if (h,d)=(-3 , -3)->0
            {
              if(strcmp(gate_pin_name, "D") == 0) 
                {
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[0][0] = -3;
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[0][1] = -3;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[0][0] = -3;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[0][1] = -3;
                }
              else if (strcmp(gate_pin_name, "CK") == 0) 
                {
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[1][0] = -3;
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[1][1] = -3;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[1][0] = -3;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[1][1] = -3;
                }
              else if (strcmp(gate_pin_name, "Q") == 0) 
                {
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[2][0] = -3;
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[2][1] = -3;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[2][0] = -3;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[2][1] = -3;
                }
              else if (strcmp(gate_pin_name, "QN") == 0) 
                {
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[3][0] = -3;
                  components_array->component_array[comp_hash_position][comp_depth].io_pins[3][1] = -3;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[3][0] = -3;
                  components_array->component_array[comp_hash_position][comp_depth].wire_pins[3][1] = -3;
                }
              
              free(gate_pin_name);
              free(component_pin_name);
              component_pin_name = NULL;
              word = strtok(NULL, " \t\n\r");
              continue;
            }
          


            
          io_array_position = hash_function(component_pin_name) % (ios_array->number_of_ios);
          wires_array_position = hash_function(component_pin_name) % (wires_array->number_of_wires);

          for(j=0; j < HASH_D_SIZE; j++)
            {
              if(ios_array->primary_io_array[io_array_position][j].valid_element == 1)
                {
                  if(strcmp(ios_array->primary_io_array[io_array_position][j].name, component_pin_name) == 0)
                    {
                      
                      
                      if (strcmp(gate_pin_name, "D") == 0) 
                        {
                          components_array->component_array[comp_hash_position][comp_depth].io_pins[0][0] = io_array_position;
                          components_array->component_array[comp_hash_position][comp_depth].io_pins[0][1] = j;
                          // printf("io pin %s found in ios_array[%lu][%d]\n", component_pin_name, io_array_position, j);

                          connect_ccs_to_wires_ios(comp_hash_position, comp_depth, 0, j, io_array_position);
                          break;
                          
                        }
                      else if (strcmp(gate_pin_name, "CK") == 0) 
                        {
                          components_array->component_array[comp_hash_position][comp_depth].io_pins[1][0] = io_array_position;
                          components_array->component_array[comp_hash_position][comp_depth].io_pins[1][1] = j;
                          // printf("io pin %s found in ios_array[%lu][%d]\n", component_pin_name, io_array_position, j);

                          connect_ccs_to_wires_ios(comp_hash_position, comp_depth, 0, j, io_array_position);
                          break;
                        }
                      else if (strcmp(gate_pin_name, "Q") == 0) 
                        {
                          components_array->component_array[comp_hash_position][comp_depth].io_pins[2][0] = io_array_position;
                          components_array->component_array[comp_hash_position][comp_depth].io_pins[2][1] = j;
                          // printf("io pin %s found in ios_array[%lu][%d]\n", component_pin_name, io_array_position, j);

                          connect_ccs_to_wires_ios(comp_hash_position, comp_depth, 0, j, io_array_position);
                          break;
                        }
                      else if (strcmp(gate_pin_name, "QN") == 0) 
                        {
                          components_array->component_array[comp_hash_position][comp_depth].io_pins[3][0] = io_array_position;
                          components_array->component_array[comp_hash_position][comp_depth].io_pins[3][1] = j;
                          // printf("io pin %s found in ios_array[%lu][%d]\n", component_pin_name, io_array_position, j);

                          connect_ccs_to_wires_ios(comp_hash_position, comp_depth, 0, j, io_array_position);
                          break;
                        }
                    }
                }
            }

          for(j=0; j < HASH_D_SIZE; j++)
            {
              if(wires_array->wire_array[wires_array_position][j].valid_element == 1)
                {
                  if(strcmp(wires_array->wire_array[wires_array_position][j].name, component_pin_name) == 0)
                    {
                      // printf("found dff in wire \n");

                      if (strcmp(gate_pin_name, "D") == 0) 
                        {
                                        
                          components_array->component_array[comp_hash_position][comp_depth].wire_pins[0][0] = wires_array_position;
                          components_array->component_array[comp_hash_position][comp_depth].wire_pins[0][1] = j;
                          // printf("wire pin %s found in wires_array[%lu][%d]\n", component_pin_name, wires_array_position, j);
                        
                          connect_ccs_to_wires_ios(comp_hash_position, comp_depth, 1, j, wires_array_position);
                          
                          break;
                        }
                      else if (strcmp(gate_pin_name, "CK") == 0) 
                        {                          
                          components_array->component_array[comp_hash_position][comp_depth].wire_pins[1][0] = wires_array_position;
                          components_array->component_array[comp_hash_position][comp_depth].wire_pins[1][1] = j;
                          // printf("wire pin %s found in wires_array[%lu][%d]\n", component_pin_name, wires_array_position, j);

                          connect_ccs_to_wires_ios(comp_hash_position, comp_depth, 1, j, wires_array_position);
                          
                          break;
                        }
                      else if (strcmp(gate_pin_name, "Q") == 0) 
                        {

                          components_array->component_array[comp_hash_position][comp_depth].wire_pins[2][0] = wires_array_position;
                          components_array->component_array[comp_hash_position][comp_depth].wire_pins[2][1] = j;
                          // printf("wire pin %s found in wires_array[%lu][%d]\n", component_pin_name, wires_array_position, j);

                          connect_ccs_to_wires_ios(comp_hash_position, comp_depth, 1, j, wires_array_position);                  
                          
                          break;
                        }
                      else if (strcmp(gate_pin_name, "QN") == 0) 
                        {                          

                          components_array->component_array[comp_hash_position][comp_depth].wire_pins[3][0] = wires_array_position;
                          components_array->component_array[comp_hash_position][comp_depth].wire_pins[3][1] = j;
                          // printf("wire pin %s found in wires_array[%lu][%d]\n", component_pin_name, wires_array_position, j);

                          connect_ccs_to_wires_ios(comp_hash_position, comp_depth, 1, j, wires_array_position);
                          break;
                        }
                    }
                }
            }
              
          free(gate_pin_name);
          free(component_pin_name);
          gate_pin_name = NULL;
          component_pin_name = NULL;
        }
          
      word = strtok(NULL, " \t\n\r"); // Read the name of the next pin of the Component//

    }
}


void create_assign_right_element_connections(int io_wire_type, unsigned long io_wire_hash, int io_wire_depth)
{
  if (io_wire_type == 0)//ios
    {
      if (ios_array->primary_io_array[io_wire_hash][io_wire_depth].num_of_assign_connections == 0)
        {
          ios_array->primary_io_array[io_wire_hash][io_wire_depth].assign_connections_array = (assign_connections *)malloc(sizeof(assign_connections));
          if (ios_array->primary_io_array[io_wire_hash][io_wire_depth].assign_connections_array == NULL) 
            {
              fprintf(stderr, "Memory allocation failed for ios_array[%lu][%d].assign_connections_array\n", io_wire_hash, io_wire_depth);
              exit(1);
            }
          ios_array->primary_io_array[io_wire_hash][io_wire_depth].num_of_assign_connections++;
        }
      else 
        {
          ios_array->primary_io_array[io_wire_hash][io_wire_depth].assign_connections_array = (assign_connections *)realloc(ios_array->primary_io_array[io_wire_hash][io_wire_depth].assign_connections_array, sizeof(assign_connections) * (ios_array->primary_io_array[io_wire_hash][io_wire_depth].num_of_assign_connections + 1));
          if (ios_array->primary_io_array[io_wire_hash][io_wire_depth].assign_connections_array == NULL) 
            {
              fprintf(stderr, "Memory allocation failed for ios_array[%lu][%d].assign_connections_array\n", io_wire_hash, io_wire_depth);
              exit(1);
            }
          ios_array->primary_io_array[io_wire_hash][io_wire_depth].num_of_assign_connections++;
        
        }
    }

  else if (io_wire_type == 1)//wire
    {
      if (wires_array->wire_array[io_wire_hash][io_wire_depth].num_of_assign_connections == 0)
        {
          wires_array->wire_array[io_wire_hash][io_wire_depth].assign_connections_array = (assign_connections *)malloc(sizeof(assign_connections));
          if (wires_array->wire_array[io_wire_hash][io_wire_depth].assign_connections_array == NULL) 
            {
              fprintf(stderr, "Memory allocation failed for wires_array[%lu][%d].assign_connections_array\n", io_wire_hash, io_wire_depth);
              exit(1);
            }
          wires_array->wire_array[io_wire_hash][io_wire_depth].num_of_assign_connections++;
        }
      else 
        {
          wires_array->wire_array[io_wire_hash][io_wire_depth].assign_connections_array = (assign_connections *)realloc(wires_array->wire_array[io_wire_hash][io_wire_depth].assign_connections_array, sizeof(assign_connections) * (wires_array->wire_array[io_wire_hash][io_wire_depth].num_of_assign_connections + 1));
          if (wires_array->wire_array[io_wire_hash][io_wire_depth].assign_connections_array == NULL) 
            {
              fprintf(stderr, "Memory allocation failed for wires_array[%lu][%d].assign_connections_array\n", io_wire_hash, io_wire_depth);
              exit(1);
            }
          wires_array->wire_array[io_wire_hash][io_wire_depth].num_of_assign_connections++;
        
        }
    }
}


void parsing_elements(FILE *file)
{
  char line[MAX_LINE_LENGTH];
  char *word;
  int type;
  int gate_type_pos;
  unsigned long comp_hash_position;
  int i, j;
  int pins_count = 0;
  unsigned long wires_array_position;
  unsigned long io_array_position;
  int comp_depth;

  unsigned long io_assign_hash_1;
  unsigned long wire_assign_hash_1;
  int io_assign_depth_1;
  int wire_assign_depth_1;

  unsigned long io_assign_hash_2;
  unsigned long wire_assign_hash_2;
  int io_assign_depth_2;
  int wire_assign_depth_2;


  printf("2nd Parsing in order to find the elements...\n");

  while ( fgets(line, sizeof(line), file) )   // Read each line 
    {
      line[strcspn(line, "\n")] = '\0';       // Remove newline character at the end of the line, if any //
      word = strtok(line, " \t\n\r");               // Split the line into words //

      if(word == NULL)                        //empty line
        {
          continue;
        }
      else if (word[0] == '/' && word[1] == '/')
        {
          continue; // Skip comment lines
        }
      else if (strcmp(word, "assign") == 0)
        {
          word = strtok(NULL, " \t\n\r"); // Read the name of the 1st element beforre = //

          io_assign_hash_1 = hash_function(word) % (ios_array->number_of_ios);
          wire_assign_hash_1 = hash_function(word) % (wires_array->number_of_wires);

          io_assign_depth_1 = -1;
          wire_assign_depth_1 = -1;
          for(i=0; i < HASH_D_SIZE; i++)
            {
              if(ios_array->primary_io_array[io_assign_hash_1][i].valid_element == 1)
                {
                  if(strcmp(ios_array->primary_io_array[io_assign_hash_1][i].name, word) == 0)
                    {
                      io_assign_depth_1 = i;
                      break;
                    }
                }
            }
          for(i=0; i < HASH_D_SIZE; i++)
            {
              if(wires_array->wire_array[wire_assign_hash_1][i].valid_element == 1)
                {
                  if(strcmp(wires_array->wire_array[wire_assign_hash_1][i].name, word) == 0)
                    {
                      wire_assign_depth_1 = i;
                      break;
                    }
                }
            }
          
          if(io_assign_depth_1 == -1 && wire_assign_depth_1 == -1)
            {
              printf("io or wire is not found\n");
              exit(1);
            }

          word = strtok(NULL, " \t\n\r"); // Read = //
          word = strtok(NULL, " \t\n\r"); // Read the name of the 2nd element after = //

          
          word[strlen(word)-1] = '\0'; // Remove the semicolon at the end of the word
          word = strdup(word);
          
          
          if ((strcmp(word, "1'b0") == 0))
            {
              if (io_assign_depth_1 != -1)
                {
                  ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].is_constant = 0;
                  
                }
              
              if (wire_assign_depth_1 != -1)
                {
                  wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].is_constant = 0;
                }

              free(word);
              word = NULL;
              continue;
            }
          else if ((strcmp(word, "1'b1") == 0))
            {
              if (io_assign_depth_1 != -1)
                {
                  ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].is_constant = 1;
                  
                }
              
              if (wire_assign_depth_1 != -1)
                {
                  wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].is_constant = 1;
                }

              free(word);
              word = NULL;
              continue;
            }

          io_assign_hash_2 = hash_function(word) % (ios_array->number_of_ios);
          wire_assign_hash_2 = hash_function(word) % (wires_array->number_of_wires);

          io_assign_depth_2 = -1;
          wire_assign_depth_2 = -1;

          for(i=0; i < HASH_D_SIZE; i++)
            {
              if(ios_array->primary_io_array[io_assign_hash_2][i].valid_element == 1)
                {
                  if(strcmp(ios_array->primary_io_array[io_assign_hash_2][i].name, word) == 0)
                    {
                      io_assign_depth_2 = i;
                      break;
                    }
                }
            }
          
          for(i=0; i < HASH_D_SIZE; i++)
            {
              if(wires_array->wire_array[wire_assign_hash_2][i].valid_element == 1)
                {
                  if(strcmp(wires_array->wire_array[wire_assign_hash_2][i].name, word) == 0)
                    {
                      wire_assign_depth_2 = i;
                      break;
                    }
                }
            }
          


          if(io_assign_depth_2 == -1 && wire_assign_depth_2 == -1)
            {
              printf("io or wire is not found 2\n");
              exit(1);
            }

          
          if(io_assign_depth_1 != -1)
            {
              if (ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].num_of_assign_connections == 0)
                {
                  ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].assign_connections_array = (assign_connections *)malloc(sizeof(assign_connections));
                  if (ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].assign_connections_array == NULL) 
                    {
                      fprintf(stderr, "Memory allocation failed for ios_array[%lu][%d].assign_connections_array\n", io_assign_hash_1, io_assign_depth_1);
                      exit(1);
                    }
                  ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].num_of_assign_connections++;
                  
                }
              else 
                {
                  ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].assign_connections_array = (assign_connections *)realloc(ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].assign_connections_array, sizeof(assign_connections) * (ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].num_of_assign_connections + 1));
                  if (ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].assign_connections_array == NULL) 
                    {
                      fprintf(stderr, "Memory allocation failed for ios_array[%lu][%d].assign_connections_array\n", io_assign_hash_1, io_assign_depth_1);
                      exit(1);
                    }
                  ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].num_of_assign_connections++;
                
                }
              
              if(wire_assign_depth_2 != -1)//io=wire
                {
                  ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].assign_connections_array[ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].num_of_assign_connections - 1].connection_hash = wire_assign_hash_2;
                  ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].assign_connections_array[ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].num_of_assign_connections - 1].connection_depth = wire_assign_depth_2;
                  ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].assign_connections_array[ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].num_of_assign_connections - 1].connection_type = 1;
                
                  create_assign_right_element_connections(1, wire_assign_hash_2, wire_assign_depth_2);
                  wires_array->wire_array[wire_assign_hash_2][wire_assign_depth_2].assign_connections_array[wires_array->wire_array[wire_assign_hash_2][wire_assign_depth_2].num_of_assign_connections - 1].connection_hash = io_assign_hash_1;
                  wires_array->wire_array[wire_assign_hash_2][wire_assign_depth_2].assign_connections_array[wires_array->wire_array[wire_assign_hash_2][wire_assign_depth_2].num_of_assign_connections - 1].connection_depth = io_assign_depth_1;
                  wires_array->wire_array[wire_assign_hash_2][wire_assign_depth_2].assign_connections_array[wires_array->wire_array[wire_assign_hash_2][wire_assign_depth_2].num_of_assign_connections - 1].connection_type = 0;
                  
                }

              if(io_assign_depth_2 != -1)//io=io
                {
                  ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].assign_connections_array[ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].num_of_assign_connections - 1].connection_hash = io_assign_hash_2;
                  ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].assign_connections_array[ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].num_of_assign_connections - 1].connection_depth = io_assign_depth_2;
                  ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].assign_connections_array[ios_array->primary_io_array[io_assign_hash_1][io_assign_depth_1].num_of_assign_connections - 1].connection_type = 0;

                  create_assign_right_element_connections(0, io_assign_hash_2, io_assign_depth_2);
                  ios_array->primary_io_array[io_assign_hash_2][io_assign_depth_2].assign_connections_array[ios_array->primary_io_array[io_assign_hash_2][io_assign_depth_2].num_of_assign_connections - 1].connection_hash = io_assign_hash_1;
                  ios_array->primary_io_array[io_assign_hash_2][io_assign_depth_2].assign_connections_array[ios_array->primary_io_array[io_assign_hash_2][io_assign_depth_2].num_of_assign_connections - 1].connection_depth = io_assign_depth_1;
                  ios_array->primary_io_array[io_assign_hash_2][io_assign_depth_2].assign_connections_array[ios_array->primary_io_array[io_assign_hash_2][io_assign_depth_2].num_of_assign_connections - 1].connection_type = 0;
                  
                }
              
            }  

          if(wire_assign_depth_1 != -1)
            {
              if (wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].num_of_assign_connections == 0)
                {
                  wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].assign_connections_array = (assign_connections *)malloc(sizeof(assign_connections));
                  if (wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].assign_connections_array == NULL) 
                    {
                      fprintf(stderr, "Memory allocation failed for ios_array[%lu][%d].assign_connections_array\n", wire_assign_hash_1, wire_assign_depth_1);
                      exit(1);
                    }
                    wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].num_of_assign_connections++;
                    
                }
              else 
                {
                  wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].assign_connections_array = (assign_connections *)realloc(wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].assign_connections_array, sizeof(assign_connections) * (wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].num_of_assign_connections + 1));
                  if (wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].assign_connections_array == NULL) 
                    {
                      fprintf(stderr, "Memory allocation failed for ios_array[%lu][%d].assign_connections_array\n", wire_assign_hash_1, wire_assign_depth_1);
                      exit(1);
                    }
                  wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].num_of_assign_connections++;
                  
                }
                

              if(wire_assign_depth_2 != -1)//wire=wire
                {
                  wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].assign_connections_array[wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].num_of_assign_connections - 1].connection_hash = wire_assign_hash_2;
                  wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].assign_connections_array[wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].num_of_assign_connections - 1].connection_depth = wire_assign_depth_2;
                  wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].assign_connections_array[wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].num_of_assign_connections - 1].connection_type = 1;
                  
                  create_assign_right_element_connections(1, wire_assign_hash_2, wire_assign_depth_2);
                  wires_array->wire_array[wire_assign_hash_2][wire_assign_depth_2].assign_connections_array[wires_array->wire_array[wire_assign_hash_2][wire_assign_depth_2].num_of_assign_connections - 1].connection_hash = wire_assign_hash_1;
                  wires_array->wire_array[wire_assign_hash_2][wire_assign_depth_2].assign_connections_array[wires_array->wire_array[wire_assign_hash_2][wire_assign_depth_2].num_of_assign_connections - 1].connection_depth = wire_assign_depth_1;
                  wires_array->wire_array[wire_assign_hash_2][wire_assign_depth_2].assign_connections_array[wires_array->wire_array[wire_assign_hash_2][wire_assign_depth_2].num_of_assign_connections - 1].connection_type = 1;
                }

              if(io_assign_depth_2 != -1)//wire=io
                {
                  wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].assign_connections_array[wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].num_of_assign_connections - 1].connection_hash = io_assign_hash_2;
                  wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].assign_connections_array[wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].num_of_assign_connections - 1].connection_depth = io_assign_depth_2;
                  wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].assign_connections_array[wires_array->wire_array[wire_assign_hash_1][wire_assign_depth_1].num_of_assign_connections - 1].connection_type = 0;
                
                  create_assign_right_element_connections(0, io_assign_hash_2, io_assign_depth_2);

                  ios_array->primary_io_array[io_assign_hash_2][io_assign_depth_2].assign_connections_array[ios_array->primary_io_array[io_assign_hash_2][io_assign_depth_2].num_of_assign_connections - 1].connection_hash = wire_assign_hash_1;
                  ios_array->primary_io_array[io_assign_hash_2][io_assign_depth_2].assign_connections_array[ios_array->primary_io_array[io_assign_hash_2][io_assign_depth_2].num_of_assign_connections - 1].connection_depth = wire_assign_depth_1;
                  ios_array->primary_io_array[io_assign_hash_2][io_assign_depth_2].assign_connections_array[ios_array->primary_io_array[io_assign_hash_2][io_assign_depth_2].num_of_assign_connections - 1].connection_type = 1;
                }
              
            }
            
          free(word);
          word = NULL;

          continue;
        }  
      else if ((strcmp(word, "wire") == 0) || (strcmp(word, "input") == 0) || (strcmp(word, "output") == 0))
        {
          if(strcmp(word, "input") == 0)
            {
              type = 0;
            }
          else if(strcmp(word, "output") == 0)
            {
              type = 1;
            }
          else 
            {
              type = 2;
            }

          word = strtok(NULL, " \t\n\r"); // Read the name of the 1st element //

          while (1)
            {
              if (word == NULL ) // No more words to read
                {
                  fgets(line, sizeof(line), file); // Read the next line
                  line[strcspn(line, "\n")] = '\0';
                  word = strtok(line, " \t\n\r"); 
                  continue; 
                }

              
              if (word[strlen(word) - 1] == ';')
                {
                  // printf("insert io/wire\n");
                  insert_io_wire(type, word);
                  break;
                }
              
              // printf("insert io/wire\n");
              insert_io_wire(type, word);

              word = strtok(NULL, " \t\n\r");
            }
        }
      else if (strcmp(word, "module") == 0)
        {
          word = strtok(NULL, " \t\n\r");
          while (1)
            {
              if (word == NULL ) // No more words to read
                {
                  fgets(line, sizeof(line), file); // Read the next line
                  line[strcspn(line, "\n")] = '\0';
                  word = strtok(line, " \t\n\r"); 
                  continue; 
                }

              if (word[strlen(word) - 1] == ';')
                {
                  break;
                }
                  
              word = strtok(NULL, " \t\n\r");
            }
        }
      else if (strcmp(word, "endmodule") == 0)
        {
          break; // End of the module
        }
      else 
        {
          //for sentence to begin with ); or ;
          if (word[strlen(word) - 1] == ';')
            {
              continue;
            }


          gate_type_pos =  find_gate_type(word);  // first word is gate type name
          if(gate_type_pos == -1)
            {
              printf("gate type is not found\n");
              exit(1);
            }
          
          word = strtok(NULL, " \t\n\r"); // Read the name of the Component //
          comp_depth = -1;
          comp_hash_position = hash_function(word) % (components_array->num_components);//insert component in the hashtable
          
          for(i=0; i < HASH_D_SIZE; i++)
            {
              if(components_array->component_array[comp_hash_position][i].valid_element == 0)
                {
                  components_array->component_array[comp_hash_position][i].valid_element = 1;
                  components_array->component_array[comp_hash_position][i].name = strdup(word);
                  components_array->component_array[comp_hash_position][i].gate_type_pos = gate_type_pos;

                  components_array->component_array[comp_hash_position][i].wire_pins = (int **)malloc(sizeof(int*) * gates_array[gate_type_pos].num_pins);
                  if (components_array->component_array[comp_hash_position][i].wire_pins == NULL) 
                    {
                      fprintf(stderr, "Memory allocation failed for component_array[%lu][%d].wire_pins\n", comp_hash_position, i);
                      exit(1);
                    }

                  components_array->component_array[comp_hash_position][i].io_pins = (int **)malloc(sizeof(int*) * gates_array[gate_type_pos].num_pins);
                  if (components_array->component_array[comp_hash_position][i].io_pins == NULL) 
                    {
                      fprintf(stderr, "Memory allocation failed for component_array[%lu][%d].io_pins\n", comp_hash_position, i);
                      exit(1);
                    }

                  for (j = 0; j < gates_array[gate_type_pos].num_pins; j++)
                    {
                      components_array->component_array[comp_hash_position][i].wire_pins[j] = (int *)malloc(sizeof(int) * 2);
                      if (components_array->component_array[comp_hash_position][i].wire_pins[j] == NULL) 
                        {
                          fprintf(stderr, "Memory allocation failed for component_array[%lu][%d].wire_pins[%d]\n", comp_hash_position, i, j);
                          exit(1);
                        }

                      components_array->component_array[comp_hash_position][i].wire_pins[j][0] = -1;
                      components_array->component_array[comp_hash_position][i].wire_pins[j][1] = -1;

                      components_array->component_array[comp_hash_position][i].io_pins[j] = (int *)malloc(sizeof(int) * 2);
                      if (components_array->component_array[comp_hash_position][i].io_pins[j] == NULL) 
                        {
                          fprintf(stderr, "Memory allocation failed for component_array[%lu][%d].io_pins[%d]\n", comp_hash_position, i, j);
                          exit(1);
                        }

                      components_array->component_array[comp_hash_position][i].io_pins[j][0] = -1;
                      components_array->component_array[comp_hash_position][i].io_pins[j][1] = -1;
                    }
                  

                  comp_depth = i;
                  break;
                }
            }

          if(comp_depth == -1)
            {
              printf("component is not found\n");
              exit(1);
            }
          

          word = strtok(NULL, " \t\n\r"); // Read "(" //
          pins_count = 0;

          if (strcmp(gates_array[gate_type_pos].name, "DFF_X1") == 0)
            {
              dff_pins(file, comp_hash_position, comp_depth);
              continue;
            }

          // for all the other components except from dff_x1 type  
          word = strtok(NULL, " \t\n\r"); // Read the name of the 1st pin of the Component//

          while(1)
            {          
              if (word == NULL ) // No more words to read
                {
                  fgets(line, sizeof(line), file); // Read the next line
                  line[strcspn(line, "\n")] = '\0';
                  word = strtok(line, " \t\n\r"); 
                  continue; 
                }

              if (word[strlen(word) - 1] == ';')
                {
                  break;
                }
            
              
              if(word[0] == '.')
                {
                  
                  if(word[strlen(word)-1] == '(' )
                    {
                      fgets(line, sizeof(line), file); // Read the next line
                      line[strcspn(line, "\n")] = '\0';
                      word = strtok(line, " \t\n\r");

                      while(word == NULL)
                        {
                          fgets(line, sizeof(line), file); // Read the next line
                          line[strcspn(line, "\n")] = '\0';
                          word = strtok(line, " \t\n\r");
                        }

                      // remove ) from the word //

                      word[strlen(word)-1] = '\0'; //remove ) from the word//
                      word = strdup(word); 
                    }
                  else 
                    {
                      word = keep_pins_special_name(word);
                    }

                    
                  if(strcmp(word, "1'b0") == 0 )  // if (h,d)=(-4 , -4)->0
                    {
                      components_array->component_array[comp_hash_position][comp_depth].io_pins[pins_count][0] = 0;
                      components_array->component_array[comp_hash_position][comp_depth].io_pins[pins_count][1] = -4;
                      
                      components_array->component_array[comp_hash_position][comp_depth].wire_pins[pins_count][0] = 0;
                      components_array->component_array[comp_hash_position][comp_depth].wire_pins[pins_count][1] = -4;
                      pins_count++;
                      free(word);
                      word = NULL;
                      word = strtok(NULL, " \t\n\r");
                      continue;
                    }
                  if(strcmp(word, "1'b1") == 0 ) //if (h,d)=(-3 , -3)->0
                    {
                      components_array->component_array[comp_hash_position][comp_depth].io_pins[pins_count][0] = 0;
                      components_array->component_array[comp_hash_position][comp_depth].io_pins[pins_count][1] = -3;
                      
                      components_array->component_array[comp_hash_position][comp_depth].wire_pins[pins_count][0] = 0;
                      components_array->component_array[comp_hash_position][comp_depth].wire_pins[pins_count][1] = -3;
                      pins_count++;
                      free(word);
                      word = NULL;
                      word = strtok(NULL, " \t\n\r");
                      continue;
                    }
                  
                  io_array_position = hash_function(word) % (ios_array->number_of_ios);
                  wires_array_position = hash_function(word) % (wires_array->number_of_wires);
                  for(j=0; j < HASH_D_SIZE; j++)
                    {
                      if(ios_array->primary_io_array[io_array_position][j].valid_element == 1)
                        {
                          if(strcmp(ios_array->primary_io_array[io_array_position][j].name, word) == 0)
                            {
                              components_array->component_array[comp_hash_position][comp_depth].io_pins[pins_count][0] = io_array_position;
                              components_array->component_array[comp_hash_position][comp_depth].io_pins[pins_count][1] = j;
                              // printf("io pin %s found in ios_array[%lu][%d]\n", word, io_array_position, j);
                              
                              connect_ccs_to_wires_ios(comp_hash_position, comp_depth, 0, j, io_array_position);
                              break;
                            }
                        }
                    }

                  for(j=0; j < HASH_D_SIZE; j++)
                    {
                      if(wires_array->wire_array[wires_array_position][j].valid_element == 1)
                        {
                          if(strcmp(wires_array->wire_array[wires_array_position][j].name, word) == 0)
                            {
                              components_array->component_array[comp_hash_position][comp_depth].wire_pins[pins_count][0] = wires_array_position;
                              components_array->component_array[comp_hash_position][comp_depth].wire_pins[pins_count][1] = j;
                              // printf("wire pin %s found in wires_array[%lu][%d]\n", word, wires_array_position, j);

                              connect_ccs_to_wires_ios(comp_hash_position, comp_depth, 1, j, wires_array_position);
                              break;
                            }
                        }
                    }
                  pins_count++;
                  free(word);
                }
                
            word = strtok(NULL, " \t\n\r"); // Read the name of the next pin of the Component//

          }

        }
      
      word = NULL;
    }
}



// Function to initialize the hash tables for primary IOs and wires after taking the proper size from 1st parsing//
void initialize_hash_tables () 
{
  unsigned long i;
  int  j;

  ios_array->primary_io_array = (primary_io **)malloc(sizeof(primary_io*) * ios_array->number_of_ios); 
  if (ios_array->primary_io_array == NULL) 
    {
      fprintf(stderr, "Memory allocation failed for primary_io_array\n");
      exit(1);
    }

  for (i = 0; i < ios_array->number_of_ios; i++) 
    {
      ios_array->primary_io_array[i] = (primary_io *)malloc(sizeof(primary_io) * HASH_D_SIZE); 
      if (ios_array->primary_io_array[i] == NULL) 
        {
          fprintf(stderr, "Memory allocation failed for primary_io_array[%lu]\n", i);
          exit(1);
        }
      for (j = 0; j < HASH_D_SIZE; j++)
        {
          ios_array->primary_io_array[i][j].valid_element = 0;
        }
    }

  wires_array->wire_array = (wire **)malloc(sizeof(wire*) * wires_array->number_of_wires); 
  if (wires_array->wire_array == NULL) 
    {
      fprintf(stderr, "Memory allocation failed for wire_array\n");
      exit(1);
    }

  for (i = 0; i < wires_array->number_of_wires; i++) 
    {
      wires_array->wire_array[i] = (wire *)malloc(sizeof(wire) * HASH_D_SIZE); 
      if (wires_array->wire_array[i] == NULL) 
        {
          fprintf(stderr, "Memory allocation failed for wire_array[%lu]\n", i);
          exit(1);
        }
      for (j = 0; j < HASH_D_SIZE; j++)
        {
          wires_array->wire_array[i][j].valid_element = 0;
        }
    }

  components_array->component_array = (component **)malloc(sizeof(component*) * components_array->num_components);
  if (components_array->component_array == NULL) 
    {
      fprintf(stderr, "Memory allocation failed for component_array\n");
      exit(1);
    }

  for (i = 0; i < components_array->num_components; i++) 
    {
      components_array->component_array[i] = (component *)malloc(sizeof(component) * HASH_D_SIZE); 
      if (components_array->component_array[i] == NULL) 
        {
          fprintf(stderr, "Memory allocation failed for component_array[%lu]\n", i);
          exit(1);
        }
      for (j = 0; j < HASH_D_SIZE; j++)
        {
          components_array->component_array[i][j].valid_element = 0;
        }
    }
}

// Function to clear the hash tables //
void clear_hast_tables()
{
  unsigned long i;
  int j, k;


  for(i = 0; i < components_array->num_components; i++)
    {
      for(j = 0; j < HASH_D_SIZE; j++)
        {
          if(components_array->component_array[i][j].valid_element == 1)
            {
              free(components_array->component_array[i][j].name);
              for (k = 0; k < gates_array[components_array->component_array[i][j].gate_type_pos].num_pins; k++)
                {
                  free(components_array->component_array[i][j].wire_pins[k]);
                  free(components_array->component_array[i][j].io_pins[k]);
                }
              free(components_array->component_array[i][j].wire_pins);
              free(components_array->component_array[i][j].io_pins);
            }
        }
      free(components_array->component_array[i]);
    }
  free(components_array->component_array);
  free(components_array);




  for (i = 0; i < gates_array_size; i++) 
    {
      free(gates_array[i].name);
      for (j = 0; j < gates_array[i].num_pins; j++)
        {
          free(gates_array[i].pin_names[j]);
        }
      free(gates_array[i].pin_names);
    }
  free(gates_array);





  for (i = 0; i < ios_array->number_of_ios; i++) 
    { 
      for(j = 0; j < HASH_D_SIZE; j++)
        {
          if(ios_array->primary_io_array[i][j].valid_element == 1)
            {
              free(ios_array->primary_io_array[i][j].name);
              for(k = 0; k < ios_array->primary_io_array[i][j].num_of_ccs + 1; k++)
                {
                  free(ios_array->primary_io_array[i][j].component_array_position[k]);
                }
              free(ios_array->primary_io_array[i][j].component_array_position);
              if(ios_array->primary_io_array[i][j].num_of_assign_connections > 0)
                {
                  free(ios_array->primary_io_array[i][j].assign_connections_array);
                }
               
            }
        }
      free(ios_array->primary_io_array[i]);
    }
  free(ios_array->primary_io_array);
  free(ios_array);


  for (i = 0; i < wires_array->number_of_wires; i++) 
    {
      for(j = 0; j < HASH_D_SIZE; j++)
        {
          if(wires_array->wire_array[i][j].valid_element == 1)
            {
              free(wires_array->wire_array[i][j].name);
              for(k = 0; k < wires_array->wire_array[i][j].num_of_ccs + 1; k++)
                {
                  free(wires_array->wire_array[i][j].component_array_position[k]);
                 
                }
              free(wires_array->wire_array[i][j].component_array_position);
              if(wires_array->wire_array[i][j].num_of_assign_connections > 0)
                {
                  free(wires_array->wire_array[i][j].assign_connections_array);
                }
            }
        }
      free(wires_array->wire_array[i]);
    }
  free(wires_array->wire_array);
  free(wires_array);

}




void print_array()
{
  unsigned long i;
  int j, k;

  printf("\n\n----------Wires Array----------\n");
  printf("Number of wires: %lu\n", wires_array->number_of_wires);
  for (i = 0; i < wires_array->number_of_wires; i++) 
    {
      printf("**********[%lu]**********\n", i );
      for (j = 0; j < HASH_D_SIZE; j++)
        {
          if(wires_array->wire_array[i][j].valid_element == 1)
            {
              printf("----->NAME = | %s |\n",wires_array->wire_array[i][j].name); 

              printf("--->ccs num is %d: ", wires_array->wire_array[i][j].num_of_ccs);
              for(k = 0; k < wires_array->wire_array[i][j].num_of_ccs; k++)
                {
                  printf("| %s | ", components_array->component_array[wires_array->wire_array[i][j].component_array_position[k][0]][wires_array->wire_array[i][j].component_array_position[k][1]].name);
                }

              printf("\n---> constant  = %d\n", wires_array->wire_array[i][j].is_constant);
              printf("--->assign connections num = %d : ", wires_array->wire_array[i][j].num_of_assign_connections);
              for(k = 0; k < wires_array->wire_array[i][j].num_of_assign_connections; k++)
                {
                  if(wires_array->wire_array[i][j].assign_connections_array[k].connection_type == 0)
                    {
                      printf("| %s - %d | ", ios_array->primary_io_array[wires_array->wire_array[i][j].assign_connections_array[k].connection_hash][wires_array->wire_array[i][j].assign_connections_array[k].connection_depth].name, wires_array->wire_array[i][j].assign_connections_array[k].connection_type);
                    }
                  else if(wires_array->wire_array[i][j].assign_connections_array[k].connection_type == 1)
                    {
                      printf("| %s - %d | ", wires_array->wire_array[wires_array->wire_array[i][j].assign_connections_array[k].connection_hash][wires_array->wire_array[i][j].assign_connections_array[k].connection_depth].name, wires_array->wire_array[i][j].assign_connections_array[k].connection_type);
                    }
                }
              printf("\n\n");
            }
          }
      printf("\n");
    }

  printf("\n\n----------Ios Array----------\n");
  printf("Number of ios: %lu\n", ios_array->number_of_ios);
  for (i = 0; i < ios_array->number_of_ios; i++) 
  {
    printf("**********[%lu]**********\n", i );
    for (j = 0; j < HASH_D_SIZE; j++)
      {
        if(ios_array->primary_io_array[i][j].valid_element == 1){
          printf("----->NAME = | %s -- %d |\n",ios_array->primary_io_array[i][j].name, ios_array->primary_io_array[i][j].in_out_io); 

          printf("--->ccs num is %d: ", ios_array->primary_io_array[i][j].num_of_ccs);
          for(k = 0; k < ios_array->primary_io_array[i][j].num_of_ccs; k++)
            {
              printf("| %s | ", components_array->component_array[ios_array->primary_io_array[i][j].component_array_position[k][0]][ios_array->primary_io_array[i][j].component_array_position[k][1]].name);
            }
          
          printf("\n---> constant  = %d\n", ios_array->primary_io_array[i][j].is_constant);
          printf("--->assign connections num = %d : ", ios_array->primary_io_array[i][j].num_of_assign_connections);
          for(k = 0; k < ios_array->primary_io_array[i][j].num_of_assign_connections; k++)
            {
              if(ios_array->primary_io_array[i][j].assign_connections_array[k].connection_type == 0)
                {
                  printf("| %s - %d | ", ios_array->primary_io_array[ios_array->primary_io_array[i][j].assign_connections_array[k].connection_hash][ios_array->primary_io_array[i][j].assign_connections_array[k].connection_depth].name, ios_array->primary_io_array[i][j].assign_connections_array[k].connection_type);

                }
              else if(ios_array->primary_io_array[i][j].assign_connections_array[k].connection_type == 1)
                {
                  printf("| %s - %d | ", wires_array->wire_array[ios_array->primary_io_array[i][j].assign_connections_array[k].connection_hash][ios_array->primary_io_array[i][j].assign_connections_array[k].connection_depth].name, ios_array->primary_io_array[i][j].assign_connections_array[k].connection_type);
                }
            }
            
          printf("\n\n");
        }
        
      }
      printf("\n");
  }


  printf("\n\n----------Gates Array----------\n");
  printf("Number of gates: %d\n", gates_array_size);
  for (i = 0; i < gates_array_size; i++) 
  {
    printf("**********[%lu]***********\n", i );
    printf("-----> NAME = | %s | \n", gates_array[i].name); 
    printf("--->pins num is %d: ", gates_array[i].num_pins);
    for (j = 0; j < gates_array[i].num_pins; j++)
      {
        printf("| %s | ", gates_array[i].pin_names[j]); 
      }
      printf("\n\n");
  }


  printf("\n\n----------Components Array----------\n");
  printf("Number of components: %lu\n", components_array->num_components);
  for (i = 0; i < components_array->num_components; i++) 
  {
    printf("**********[%lu]**********\n", i );
    for (j = 0; j < HASH_D_SIZE; j++)
      {
        if(components_array->component_array[i][j].valid_element == 1)
          {
            printf("----->NAME = | %s | \n",components_array->component_array[i][j].name); 
            printf("---> Gate type: %s\n", gates_array[components_array->component_array[i][j].gate_type_pos].name);

            printf("--->pins num is %d: ", gates_array[components_array->component_array[i][j].gate_type_pos].num_pins);
            for (k = 0; k < gates_array[components_array->component_array[i][j].gate_type_pos].num_pins; k++)
              {
                //it is the same if i print ios for the 2 occasions//
                if((components_array->component_array[i][j].wire_pins[k][0] == 0) && (components_array->component_array[i][j].wire_pins[k][1] == -3))
                  {
                    printf("| wire/io=constant = 1'b1 | "); 
                    continue;
                  }
                if((components_array->component_array[i][j].wire_pins[k][0] == 0) && (components_array->component_array[i][j].wire_pins[k][1] == -4))
                  {
                    printf("| wire/io=constant = 1'b0 | "); 
                    continue; 
                  }

                if((components_array->component_array[i][j].wire_pins[k][0] != -1) && (components_array->component_array[i][j].wire_pins[k][1] != -1))
                  {
                    printf("| wire = %s | ", wires_array->wire_array[components_array->component_array[i][j].wire_pins[k][0]][components_array->component_array[i][j].wire_pins[k][1]].name); 
                  }
                
                if((components_array->component_array[i][j].io_pins[k][0] != -1) && (components_array->component_array[i][j].io_pins[k][1] != -1))
                  {
                    printf("|io =  %s | ", ios_array->primary_io_array[components_array->component_array[i][j].io_pins[k][0]][components_array->component_array[i][j].io_pins[k][1]].name); 
                  }

                if((components_array->component_array[i][j].wire_pins[k][0] == -1) && (components_array->component_array[i][j].wire_pins[k][1] == -1) && (components_array->component_array[i][j].io_pins[k][0] == -1) && (components_array->component_array[i][j].io_pins[k][1] == -1))
                  {
                    printf("| - | "); 
                  }
                               
                
              }
              printf("\n\n");
            }
        }
    }
}

int main(int argc, char *argv[])
{
  int iteration;
  FILE *file;

  iteration = 2;

  if (argc < 2) 
    {
      fprintf(stderr, "Incorrect number of arguments. It must be %s <file_path>\n", argv[0]);
      return 1;
    }
  while (iteration != 0)
    {
      file = fopen(argv[1], "r");  
      if (file == NULL) 
        {
          perror("Error opening file");
          return 1;
        }
    
      if (iteration == 2) // 1st iteration //
        {
          ios_array = (primary_ios_hash *)malloc(sizeof(primary_ios_hash));
          if (ios_array == NULL) 
            {
              fprintf(stderr, "Memory allocation failed for ios_array\n");
              fclose(file);
              return 1;
            }
          ios_array->number_of_ios = 0;


          wires_array = (wires_hash *)malloc(sizeof(wires_hash));
          if (wires_array == NULL) 
            {
              fprintf(stderr, "Memory allocation failed for wires_array\n");
              fclose(file);
              return 1;
            }
          wires_array->number_of_wires = 0;

          components_array = (component_hash *)malloc(sizeof(component_hash));
          if (components_array == NULL) 
            {
              fprintf(stderr, "Memory allocation failed for components_array\n");
              fclose(file);
              return 1;
            }
          components_array->num_components = 0;
        
          gates_array = (gate *)malloc(sizeof(gate));

          parsing_number_of_elements(file);
          initialize_hash_tables();
        }

      if (iteration == 1)
        {
          parsing_elements(file);

        }

      fclose(file);
      iteration = iteration - 1;
    }

  print_array();
  clear_hast_tables();
  return 0;
}



