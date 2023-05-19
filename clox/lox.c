/***
* @author: jmpnz
* @brief: Implementation of lox described in craftinginterpreters.com
* @file: lox.c is a literate C implementation of the Lox bytecode VM.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

/***
 * Why a bytecode VM ?
 * - Memory efficiency because a tree-walk interpreter ends up
 *   with a slew of objects and pointers.
 * - We can do nifty with a VM such as tracing execution and possibly
 *   JITing native code
 * - It's fun
***/


/// Define some memory allocation utilities.

// reallocate takes care of allocation, reallocation and free-ing memory.
void* reallocate(void* pointer, size_t old_size, size_t new_size) {
  if (new_size == 0) {
    free(pointer);
    return NULL;
  }
  void *result = realloc(pointer, new_size);
  if (result == NULL) exit(1);
  return result;
}


#define GROW_CAPACITY(capacity) ((capacity < 8 ? 8 : (capacity) * 2))
#define GROW_ARRAY(type, pointer, old_count, new_count) \
  (type*)reallocate(pointer, sizeof(type) * (old_count), sizeof(type) * (new_count))

#define FREE_ARRAY(type, pointer, old_count) reallocate(pointer, sizeof(type) * old_count, 0)


/// Define our Value type (NaN boxing)
typedef double Value ;

// Similarly to the JVM we associate a ValueArray
// to our VM that works like a constant pool, this is useful
// for handling literal integer or float values.
typedef struct {
  int capacity;
  int count;
  Value* values;
} ValueArray;

void initValueArray(ValueArray* array) {
  array->values = NULL;
  array->count = 0;
  array->capacity = 0;
}

void writeValueArray(ValueArray* array, Value value) {
  if (array->capacity < array->count + 1) {
    int old_capacity = array->capacity;
    array->capacity = GROW_CAPACITY(old_capacity);
    array->values = GROW_ARRAY(Value, array->values, old_capacity, array->capacity);
  }
  array->values[array->count] = value;
  array->count++;
}

void freeValueArray(ValueArray* array) {
  FREE_ARRAY(Value, array->values,array->capacity);
  initValueArray(array);
}

void printValue(Value value) {
  printf("%g", value);
}


// OPCode represents a single opcode for our bytecode VM.
// Each OPCode is 1 byte.
typedef enum {
  OP_CONSTANT, // 2 byte OPCode [OPCode, Operand]
  OP_RETURN,
} OPCode;

// Chunk represents our instructions
typedef struct {
  // capacity stores how much we allocated for the code byte array.
  int capacity;
  // count stores how much of our allocated bytes are in-use.
  int count;
  // our instructions will be stored in a byte array.
  uint8_t* code;
  // our constants pool
  ValueArray constants;
} Chunk;

/// Chunk functions
void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte) {
  if (chunk->capacity < chunk->count + 1) {
    int old_capacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(old_capacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code,old_capacity,chunk->capacity);
  }
  chunk->code[chunk->count] = byte;
  chunk->count++;
}

int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}



/// Debug functions
static int simpleInstruction(const char* name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
  uint8_t constant = chunk->code[offset + 1];
  printf("%-16s %4d '", name, constant);
  printValue(chunk->constants.values[constant]);
  printf("'\n");
  return offset + 2;
}

int disassembleInstruction(Chunk* chunk, int offset) {
  printf("%04d ", offset);

  uint8_t instruction = chunk->code[offset];
  switch (instruction) {
    case OP_RETURN:
      return simpleInstruction("OP_RETURN", offset);
    case OP_CONSTANT:
      return constantInstruction("OP_CONSTANT", chunk, offset);
    default:
      printf("Unknown opcde %d\n", instruction);
      // increment offset by the size of the instruction
      return offset + 1;
  }
}

void disassembleChunk(Chunk* chunk, const char* name) {
  printf("== %s ==\n", name);

  for (int offset = 0; offset < chunk->count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}


int main() {
  Chunk chunk;
  initChunk(&chunk);
  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT);
  writeChunk(&chunk, constant);
  writeChunk(&chunk,OP_RETURN);
  disassembleChunk(&chunk, "test_program");
  freeChunk(&chunk);
}

