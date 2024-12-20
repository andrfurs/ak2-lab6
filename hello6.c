
/*
 * Copyright (c) 2017, GlobalLogic Ukraine LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the GlobalLogic.
 * 4. Neither the name of the GlobalLogic nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GLOBALLOGIC UKRAINE LLC ``AS IS`` AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC UKRAINE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>

MODULE_AUTHOR("Andrii Fursenko");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static uint print_count = 1;
module_param(print_count, uint, 0444);
MODULE_PARM_DESC(print_count, "Number of times to print 'Hello, world!'");

struct event_list {
	struct list_head list;
	ktime_t event_time;
};

static struct list_head event_list_head;
static LIST_HEAD(event_list_head);
void new_event(void);

static int __init hello_init(void)
{
	uint i;
	struct event_list *element = NULL;

	if (print_count == 0 || (print_count >= 5 && print_count <= 10)) {
		printk(KERN_EMERG "Warning: print_count is 0 or between 5 and 10.\n");
	} else if (print_count > 10) {
		BUG_ON(1);
	}
	for (i = 0; i < print_count; i++) {
		if (i == 7) {
			element == NULL;
		} else {
			element = kmalloc(sizeof(struct event_list), GFP_KERNEL);
		}
		
		BUG_ON(!element);

		element->event_time = ktime_get();
		list_add_tail(&element->list, &event_list_head);

		printk(KERN_EMERG "Hello, world!\n");
	}
	return 0;
}

static void __exit hello_exit(void)
{
	struct event_list *md, *tmp;

	list_for_each_entry_safe(md, tmp, &event_list_head, list) {
		printk(KERN_EMERG "Time: %lld\n", md->event_time);
		list_del(&md->list);
		kfree(md);
	}
}

module_init(hello_init);
module_exit(hello_exit);
