#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json_list.h"

JObject* parse_json(const char *filename) {
    json_error_t error;
    json_t *root = json_load_file(filename, 0, &error);

    if (!root || !json_is_array(root)) {
        fprintf(stderr, "Erreur: %s:%d: %s\n", error.source, error.line, error.text);
        if (root) json_decref(root);
        return NULL;
    }

    JObject *head = NULL;

    size_t index;
    json_t *value;
    json_array_foreach(root, index, value) {
        if (!json_is_object(value)) continue;

        json_t *jname = json_object_get(value, "name");
        json_t *jage = json_object_get(value, "age");

        if (!json_is_string(jname) || !json_is_integer(jage)) continue;

        JObject *node = malloc(sizeof(JObject));
        node->name = strdup(json_string_value(jname));
        node->age = (int)json_integer_value(jage);
        node->next = head;
        head = node;
    }

    json_decref(root);
    return head;
}

void print_list(JObject *head) {
    for (JObject *p = head; p; p = p->next) {
        printf("Name: %s | Age: %d\n", p->name, p->age);
    }
}

void free_list(JObject *head) {
    while (head) {
        JObject *tmp = head;
        head = head->next;
        free(tmp->name);
        free(tmp);
    }
}
