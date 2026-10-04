/* Shims for kernel APIs removed after 6.14, force-included by the Makefile. */
#ifndef _AICWF_KCOMPAT_H_
#define _AICWF_KCOMPAT_H_

#include <linux/version.h>
#include <linux/timer.h>
#include <linux/preempt.h>

/* 6.15 dropped del_timer*() for timer_delete*() (available since 6.2). */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 15, 0)
#define del_timer(t)		timer_delete(t)
#define del_timer_sync(t)	timer_delete_sync(t)
#endif

/* 6.16 renamed from_timer() to timer_container_of(). */
#ifndef from_timer
#define from_timer(var, callback_timer, timer_fieldname) \
	timer_container_of(var, callback_timer, timer_fieldname)
#endif

/* 7.0 dropped in_irq(). */
#ifndef in_irq
#define in_irq()		in_hardirq()
#endif

#endif /* _AICWF_KCOMPAT_H_ */
