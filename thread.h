/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** headers
*/

#ifndef _THREAD_H
#define _THREAD_H

void thread_init(void);
void thread_quit(void);
void thread_wait(void);

void thread_send(size_t ndx, thread_task task, uint64_t *data, size_t size);
void thread_send_each(thread_task task, uint64_t *data, size_t size);
void thread_do_task(thread_bus *bus);

#endif
