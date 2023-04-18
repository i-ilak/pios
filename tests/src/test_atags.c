#include "include/test_atags.h"

#include "../os/include/kernel/atag.h"

static atag_t *params; /* used to point at the current tag */

static void setup_core_tag(uint32_t *loc, long pagesize)
{
  params = (atag_t *)loc; /* Initialise parameters to start at given address */

  params->header.tag_type = ATAG_CORE;       /* start with the core tag */
  params->header.size = tag_size(atag_core); /* size the tag */

  params->core.flags = 1;           /* ensure read-only */
  params->core.pagesize = pagesize; /* systems pagesize (4k) */
  params->core.rootdevice
    = 0; /* zero root device (typicaly overidden from commandline )*/

  params = tag_next(params); /* move pointer to next tag */
}

static void setup_mem_tag(uint32_t start, uint32_t len)
{
  params->header.tag_type = ATAG_MEM;       /* Memory tag */
  params->header.size = tag_size(atag_mem); /* size tag */

  params->mem.address = start; /* Start of memory area (physical address) */
  params->mem.size = len;      /* Length of area */

  params = tag_next(params); /* move pointer to next tag */
}

static void setup_end_tag()
{
  params->header.tag_type = ATAG_NONE; /* Empty tag ends list */
  params->header.size = 0;             /* zero length */
}

void setup_atags(uint32_t *loc)
{
  setup_core_tag(loc, 4096);
  setup_mem_tag(0, 4096);
  setup_end_tag();
}

void test_ram_calculation(uint32_t *atags)
{
  assert_int_equal(4096, get_mem_size((atag_t *)atags));
}

void test_atag_core(atag_t *atags)
{
  assert_int_equal(atags->header.tag_type, ATAG_CORE);

  assert_int_equal(atags->core.flags, 1);
  assert_int_equal(atags->core.pagesize, 4096);
  assert_int_equal(atags->core.rootdevice, 0);
}

void test_atag_mem(atag_t *atags)
{
  assert_int_equal(atags->header.tag_type, ATAG_MEM);

  assert_int_equal(atags->mem.size, 4096);
  assert_int_equal(atags->mem.address, 0);
}

void test_atag_end(atag_t *atags)
{
  assert_int_equal(atags->header.tag_type, ATAG_NONE);
}

void test_atags(void **state)
{
  (void)state;
  uint32_t *space_for_atags = calloc(1000, sizeof(uint32_t));
  setup_atags(space_for_atags);

  atag_t *atags = (atag_t *)space_for_atags;
  test_ram_calculation(space_for_atags);
  test_atag_core(atags);
  atags = tag_next(atags);
  test_atag_mem(atags);
  atags = tag_next(atags);
  test_atag_end(atags);

  free(space_for_atags); // also free's atags
}