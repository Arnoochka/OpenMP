#include <stdio.h>
#include <stdlib.h>
#include "Vectors.h"

typedef struct Pair {
    vector_t first;
    vector_t second;
} pair_t;

typedef struct Buffer {
    pair_t* data;
    int front; // Индекс начала буффера
    int rear;  // Индекс конца буффера
    int size;  // Текущий размер буффера
    int max_size; // максимальный размер буффера
} buffer_t;

// Инициализация очереди
buffer_t init_buffer(int max_size) {
    buffer_t q;
    q.max_size = max_size;
    q.data = (pair_t *)malloc(sizeof(pair_t) * max_size);
    q.front = 0;
    q.rear = -1;
    q.size = 0;

    return q;
}

// Проверка на пустоту
int isEmpty(buffer_t* q) {
    return q->size == 0;
}

// Проверка на заполненность
int isFull(buffer_t* q) {
    return q->size == q->max_size;
}

// Добавление элемента в очередь
void enbuffer(buffer_t* q, pair_t* value) {
    if (isFull(q)) {
        printf("Очередь переполнена! Невозможно добавить элемент\n");
        return;
    }
    q->rear = (q->rear + 1) % q->max_size;
    pair_t new_value;
    new_value.first = vector_copy(&value->first);
    new_value.second = vector_copy(&value->second);
    q->data[q->rear] = new_value;
    q->size++;
}

// Удаление элемента из очереди
pair_t debuffer(buffer_t* q) {
    if (isEmpty(q)) {
        printf("Очередь пуста! Невозможно удалить элемент\n");
        pair_t pair;
        return pair;
    }
    pair_t value = q->data[q->front];
    q->front = (q->front + 1) % q->max_size;
    q->size--;
    return value;
}
