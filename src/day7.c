#include "day7.h"
#include "util.h"
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_MAX_ARGUMENTS 3
#define MAX_FOLDER_COUNT_SIZE 100000
#define DISK_SPACE_AVAILABLE 70000000
#define MIN_UNUSED_SPACE 30000000

typedef struct FileSystemNode {
  char *name;
  unsigned int size;
  struct FileSystemNode *parent;
  bool is_folder;
  List *child_nodes;
} FileSystemNode;

static FileSystemNode *file_system_node_new_file(char *name, int size,
                                                 FileSystemNode *parent) {
  FileSystemNode *this = malloc(sizeof(FileSystemNode));
  this->name = strdup(name);
  this->size = size;
  this->parent = parent;
  this->is_folder = false;
  this->child_nodes = NULL;
  return this;
}

static FileSystemNode *file_system_node_new_folder(char *name,
                                                   FileSystemNode *parent) {
  FileSystemNode *this = malloc(sizeof(FileSystemNode));
  this->name = strdup(name);
  this->size = 0;
  this->parent = parent;
  this->is_folder = true;
  this->child_nodes = list_new();
  return this;
}

static FileSystemNode *file_system_node_find_node(FileSystemNode *this,
                                                  char *name) {
  assert(this);
  assert(this->is_folder);
  for (int i = 0; i < list_length(this->child_nodes); i++) {
    FileSystemNode *file = list_get(this->child_nodes, i);
    if (strcmp(file->name, name) == 0) {
      return file;
    }
  }
  return NULL;
}

static void file_system_node_add_node(FileSystemNode *this,
                                      FileSystemNode *node) {
  assert(this);
  assert(node);
  assert(this->is_folder);
  FileSystemNode *tmp = file_system_node_find_node(this, node->name);
  if (tmp) {
    return;
  }
  node->parent = this;
  list_push(this->child_nodes, node);
}

static void file_system_node_free(FileSystemNode *this) {
  free(this->name);
  free(this->child_nodes);
  free(this);
}

typedef void (*WalkFunction)(FileSystemNode *node, void *data);

static void file_system_node_walk(FileSystemNode *this, void *data,
                                  WalkFunction f) {
  assert(this);
  f(this, data);
  if (this->is_folder) {
    for (int i = 0; i < list_length(this->child_nodes); i++) {
      FileSystemNode *child = list_get(this->child_nodes, i);
      file_system_node_walk(child, data, f);
    }
  }
}

static void file_system_node_recurisve_free_walker(FileSystemNode *node,
                                                   void *data) {
  file_system_node_free(node);
}

static void file_system_node_recurisve_free(FileSystemNode *this) {
  file_system_node_walk(this, NULL, file_system_node_recurisve_free_walker);
}

static void file_system_node_print(FileSystemNode *this, int indent) {
  printf("%*s - %s ", indent, "", this->name);
  if (this->is_folder) {
    printf("(dir)\n");
    for (int i = 0; i < list_length(this->child_nodes); i++) {
      FileSystemNode *child = list_get(this->child_nodes, i);
      file_system_node_print(child, indent + 2);
    }
  } else {
    printf("(file, size=%u)\n", this->size);
  }
}

static char **split_line(char *line) {
  char **command = calloc(COMMAND_MAX_ARGUMENTS, sizeof(char *));
  char *argument = strtok(line, " ");
  int index = 0;
  while (argument != NULL) {
    command[index] = strdup(argument);
    argument = strtok(NULL, " ");
    index++;
  }
  return command;
}

static void free_split(char **command) {
  for (int i = 0; i < COMMAND_MAX_ARGUMENTS; i++) {
    free(command[i]);
  }
  free(command);
}

static int get_recursive_folder_size(FileSystemNode *node) {
  int size = 0;
  assert(node->is_folder);
  size_t length = list_length(node->child_nodes);
  if (length == 0) {
    return 0;
  }
  for (int i = 0; i < length; i++) {
    FileSystemNode *child = list_get(node->child_nodes, i);
    assert(child);
    size = size + child->size;
    if (child->is_folder) {
      size = size + get_recursive_folder_size(child);
    }
  }
  return size;
}

static void count_size_more_than_1000(FileSystemNode *node, void *data) {
  int *count = (int *)data;
  assert(node);
  if (!node->is_folder) {
    return;
  }
  int count_folder = get_recursive_folder_size(node);
  if (count_folder <= MAX_FOLDER_COUNT_SIZE) {
    *count = *count + count_folder;
  }
}

typedef struct FindSmallestFolderToDelete {
  FileSystemNode *current;
  int difference;
  int current_free_space;
} FindSmallestFolderToDelete;

static void find_smallest_folder_to_delete_walker(FileSystemNode *node,
                                                  void *data) {
  FindSmallestFolderToDelete *find_smallest_folder_to_delete_data =
      (FindSmallestFolderToDelete *)data;
  if (!node->is_folder) {
    return;
  }
  int folder_size = get_recursive_folder_size(node);
  int difference =
      (find_smallest_folder_to_delete_data->current_free_space + folder_size) -
      MIN_UNUSED_SPACE;
  if (difference < 0) {
    return;
  }
  if (difference < find_smallest_folder_to_delete_data->difference) {
    find_smallest_folder_to_delete_data->difference = difference;
    find_smallest_folder_to_delete_data->current = node;
    return;
  }
  return;
}

void day7(void) {
  FileSystemNode *root = file_system_node_new_folder("/", NULL);
  FileSystemNode *current_directory = root;
  FILE *input = fopen("./inputs/input7.txt", "r");
  char *line;
  char buffer[100];
  while ((line = fgets(buffer, sizeof buffer, input))) {
    if (line[0] == '$') {
      char **command = split_line(line + 2);
      if (strncmp(command[0], "cd", 2) == 0) {
        char *folder_name = command[1];
        folder_name[strlen(folder_name) - 1] = '\0';
        if (strncmp(folder_name, "..", 2) == 0) {
          assert(current_directory->parent);
          current_directory = current_directory->parent;
          free_split(command);
          continue;
        }
        if (strncmp(folder_name, "/", 1) == 0) {
          current_directory = root;
          free_split(command);
          continue;
        }
        FileSystemNode *new_directory =
            file_system_node_find_node(current_directory, folder_name);
        assert(new_directory);
        current_directory = new_directory;
        free_split(command);
        continue;
      }
      free_split(command);
    }
    if (line[0] == 'd') {
      char **output = split_line(line);
      char *folder_name = output[1];
      assert(folder_name);
      folder_name[strlen(folder_name) - 1] = '\0';
      FileSystemNode *new_folder =
          file_system_node_new_folder(folder_name, current_directory);
      file_system_node_add_node(current_directory, new_folder);
      free_split(output);
      continue;
    }
    if (isdigit(line[0])) {
      char **output = split_line(line);
      int size = parse_number(output[0]);
      assert(output[1]);
      char *file_name = output[1];
      file_name[strlen(file_name) - 1] = '\0';
      FileSystemNode *new_file =
          file_system_node_new_file(file_name, size, current_directory);
      file_system_node_add_node(current_directory, new_file);
      free_split(output);
    }
  }
  printf("\n");
  file_system_node_print(root, 0);
  int *count = malloc(sizeof(int));
  *count = 0;
  file_system_node_walk(root, (void *)count, count_size_more_than_1000);
  printf("count: %i\n", *count);
  free(count);

  int used_size = get_recursive_folder_size(root);
  int current_free_space = DISK_SPACE_AVAILABLE - used_size;
  FindSmallestFolderToDelete *find_smallest_folder_to_delete_data =
      malloc(sizeof(FindSmallestFolderToDelete));
  find_smallest_folder_to_delete_data->current = NULL;
  find_smallest_folder_to_delete_data->difference = INT_MAX;
  find_smallest_folder_to_delete_data->current_free_space = current_free_space;
  file_system_node_walk(root, find_smallest_folder_to_delete_data,
                        find_smallest_folder_to_delete_walker);

  assert(find_smallest_folder_to_delete_data->current);
  printf(
      "Folder to delete: %s (size=%i)\n",
      find_smallest_folder_to_delete_data->current->name,
      get_recursive_folder_size(find_smallest_folder_to_delete_data->current));

  free(find_smallest_folder_to_delete_data);
  file_system_node_recurisve_free(root);
}
