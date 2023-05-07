#include <stdint.h>
#include "atag.h"
#include "list.h"
#ifndef MEMORY_H
#define MEMORY_H /**< MEMORY_H */

/**
 * @file memory.h
 * @brief Memory management
 */

#define PAGE_SIZE 4096                 /**< Page size */
#define KERNEL_HEAP_SIZE (1024 * 1024) /**< Kernel heap size */
#define KERNEL_STACK_SIZE PAGE_SIZE    /**< Kernel stack size */

/**
 * @brief Page flags
 *
 * This is a bit field that describes the state of a page. It is stored in the
 * page_t structure. The flags are: allocated, kernel_page, kernel_heap_page.
 * The remaining bits are reserved.
 */
typedef struct
{
    uint8_t allocated : 1;        /**< This page is allocated to something */
    uint8_t kernel_page : 1;      /**< This page is a part of the kernel */
    uint8_t kernel_heap_page : 1; /**< This page is a part of the kernel */
    uint32_t reserved : 29;       /**< Reserved */
} page_flags_t;                   /**< Page flags */

DEFINE_LIST(page); /**< List of pages */

/**
 * @brief Page
 *
 * This structure describes a page. It is used to keep track of the state of
 * each page in the system. It is stored in the page itself, so it is not
 * possible to allocate a page for the page structure itself.
 */
typedef struct page
{
    uint32_t vaddr_mapped; /**< Virtual address mapped to this page */
    page_flags_t flags;    /**< Page flags */
    DEFINE_LINK(page);     /**< Link to the next page */
} page_t;                  /**< Page */

/**
 * @brief Kernel heap
 *
 * This is a linked list of pages that are allocated to the kernel heap.
 */
void mem_init(atag_t *atags);

/**
 * @brief Allocate a page
 *
 * Allocates a page of physical memory. It gets a free page from a list of free
 * pages, updates its metadata to mark it as allocated, and zeros out the
 * page's contents.
 *
 * @return Pointer to the allocated page
 */
void *alloc_page(void);

/**
 * @brief Free a page
 *
 * This function frees a page that was previously allocated with alloc_page().
 * If the page was not allocated with alloc_page(), the behavior is undefined.
 *
 * @param ptr Pointer to the page to free
 */
void free_page(void *ptr);

/**
 * @brief Allocate a page for the kernel heap
 *
 * This function allocates a block of memory from the kernel heap. It
 * takes the number of bytes to allocate as a parameter, finds the best fit
 * free segment in the heap, allocates the segment, and returns a pointer to
 * the memory block that has been allocated. The returned pointer points to the
 * memory block that starts immediately after the segment header, which
 * contains information about the size of the segment and whether it has been
 * allocated or not.
 *
 * @return Pointer to the allocated page
 */
void *kmalloc(uint32_t bytes);

/**
 * @brief Free a block of memory from the kernel heap
 *
 * This function frees a block of memory that was previously allocated with
 * kmalloc(). If the block was not allocated with kmalloc(), the behavior is
 * undefined.
 *
 * @param ptr Pointer to the block of memory to free
 */
void kfree(void *ptr);

#endif // MEMORY_H