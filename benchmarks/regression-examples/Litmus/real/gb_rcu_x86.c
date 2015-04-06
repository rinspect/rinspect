#include <pthread.h>
#include <assert.h>

// c::tag-#anon#UN[SYM#c::tag-raw_spinlock#'rlock']
// 
union anon$1;

// c::tag-#anon#UN[U32'head_tail'|SYM#c::tag-__raw_tickets#'tickets']
// 
union anon$0;

// c::tag-__raw_tickets
// file linux-3.2.21/arch/x86/include/asm/spinlock_types.h line 24
struct __raw_tickets;

// c::tag-arch_spinlock
// file linux-3.2.21/arch/x86/include/asm/spinlock_types.h line 21
struct arch_spinlock;

// c::tag-foo
// file rcu_harness.c line 13
struct foo;

// c::tag-raw_spinlock
// file linux-3.2.21/include/linux/spinlock_types.h line 20
struct raw_spinlock;

// c::tag-spinlock
// file linux-3.2.21/include/linux/spinlock_types.h line 64
struct spinlock;


#ifndef TRUE
#define TRUE (_Bool)1
#endif
#ifndef FALSE
#define FALSE (_Bool)0
#endif
#ifndef NULL
#define NULL ((void*)0)
#endif
#ifndef FENCE
#define FENCE(x) ((void)0)
#endif
#ifndef IEEE_FLOAT_EQUAL
#define IEEE_FLOAT_EQUAL(x,y) (x==y)
#endif
#ifndef IEEE_FLOAT_NOTEQUAL
#define IEEE_FLOAT_NOTEQUAL(x,y) (x!=y)
#endif

// c::__raw_spin_unlock
// file linux-3.2.21/include/linux/spinlock_api_smp.h line 149
static void __raw_spin_unlock(struct raw_spinlock *lock);
// c::__rcu_read_lock
// file linux-3.2.21/include/linux/rcupdate.h line 153
static void __rcu_read_lock(void);
// c::__rcu_read_unlock
// file linux-3.2.21/include/linux/rcupdate.h line 158
static void __rcu_read_unlock(void);
// c::__ticket_spin_unlock
// file linux-3.2.21/arch/x86/include/asm/spinlock.h line 91
static void __ticket_spin_unlock(struct arch_spinlock *lock);
// c::_raw_spin_lock
// file linux-3.2.21/include/linux/spinlock_api_smp.h line 22
void _raw_spin_lock(struct raw_spinlock *);
// c::arch_spin_unlock
// file linux-3.2.21/arch/x86/include/asm/spinlock.h line 137
static void arch_spin_unlock(struct arch_spinlock *lock);
// c::do_raw_spin_unlock
// file linux-3.2.21/include/linux/spinlock.h line 155
static void do_raw_spin_unlock(struct raw_spinlock *lock);
// c::foo_get_a
// file rcu_harness.c line 63
int foo_get_a(void);
// c::foo_update_a
// file rcu_harness.c line 38
void* foo_update_a(int new_a);// modify by nlz
// c::rcu_read_lock
// file linux-3.2.21/include/linux/rcupdate.h line 636
static void rcu_read_lock(void);
// c::rcu_read_unlock
// file linux-3.2.21/include/linux/rcupdate.h line 658
static void rcu_read_unlock(void);
// c::spin_lock
// file linux-3.2.21/include/linux/spinlock.h line 283
static void spin_lock(struct spinlock *lock);
// c::spin_unlock
// file linux-3.2.21/include/linux/spinlock.h line 323
static void spin_unlock(struct spinlock *lock);
// c::synchronize_rcu
// file linux-3.2.21/include/linux/rcupdate.h line 163
static void synchronize_rcu(void);
// c::synchronize_sched
// file linux-3.2.21/include/linux/rcupdate.h line 135
void synchronize_sched(void);

struct __raw_tickets
{
  // head
  unsigned short int head;
  // tail
  unsigned short int tail;
};

union anon$0
{
  // head_tail
  unsigned int head_tail;
  // tickets
  struct __raw_tickets tickets;
};

struct arch_spinlock
{
  // $anon0
  union anon$0 $anon0;
};

struct raw_spinlock
{
  // raw_lock
  struct arch_spinlock raw_lock;
};

union anon$1
{
  // rlock
  struct raw_spinlock rlock;
};

struct foo
{
  // a
  int a;
  // b
  signed char b;
  // c
  long int c;
};

struct spinlock
{
  // $anon0
  union anon$1 $anon0;
};


// c::foo1
// file rcu_harness.c line 21
struct foo foo1;
// c::foo1
// file rcu_harness.c line 21
struct foo foo1 = { .a=0, .b=0, .c=0 };
// c::foo2
// file rcu_harness.c line 21
struct foo foo2;
// c::foo2
// file rcu_harness.c line 21
struct foo foo2 = { .a=0, .b=0, .c=0 };
// c::foo_mutex
// file rcu_harness.c line 23
struct spinlock foo_mutex;
// c::foo_mutex
// file rcu_harness.c line 23
struct spinlock foo_mutex = { .$anon0={ .rlock={ .raw_lock={ .$anon0={ .head_tail=(unsigned int)0 } } } } };
// c::gbl_foo
// file rcu_harness.c line 19
struct foo *gbl_foo;
// c::gbl_foo
// file rcu_harness.c line 19
struct foo *gbl_foo = ((struct foo *)NULL);

// c::__raw_spin_unlock
// file linux-3.2.21/include/linux/spinlock_api_smp.h line 149
static void __raw_spin_unlock(struct raw_spinlock *lock)
{

//__CPROVER_DUMP_L1:
  ;
  do_raw_spin_unlock(lock);

//__CPROVER_DUMP_L2:
  ;
}

// c::__rcu_read_lock
// file linux-3.2.21/include/linux/rcupdate.h line 153
static void __rcu_read_lock(void)
{

//__CPROVER_DUMP_L1:
  ;
}

// c::__rcu_read_unlock
// file linux-3.2.21/include/linux/rcupdate.h line 158
static void __rcu_read_unlock(void)
{

//__CPROVER_DUMP_L1:
  ;
}

// c::__ticket_spin_unlock
// file linux-3.2.21/arch/x86/include/asm/spinlock.h line 91
static void __ticket_spin_unlock(struct arch_spinlock *lock)
{
  asm("incw %0");
}

// c::arch_spin_unlock
// file linux-3.2.21/arch/x86/include/asm/spinlock.h line 137
static void arch_spin_unlock(struct arch_spinlock *lock)
{
  __ticket_spin_unlock(lock);
}

// c::do_raw_spin_unlock
// file linux-3.2.21/include/linux/spinlock.h line 155
static void do_raw_spin_unlock(struct raw_spinlock *lock)
{
  arch_spin_unlock(&lock->raw_lock);
  (void)0;
}

// c::foo_get_a
// file rcu_harness.c line 63
int foo_get_a(void)
{
  int retval;
  rcu_read_lock();
  struct foo *_________p1 = (struct foo *)*((struct foo * volatile *)&gbl_foo);

//__CPROVER_DUMP_L1:
  ;

//__CPROVER_DUMP_L2:
  ;
  retval = ((struct foo *)_________p1)->a;
  rcu_read_unlock();
  return retval;
}

// c::foo_update_a
// file rcu_harness.c line 38
void* foo_update_a(int new_a)
{
  struct foo *new_fp;
  struct foo *old_fp;
  new_fp = &foo2;
  spin_lock(&foo_mutex);
  old_fp = gbl_foo;
  *new_fp = *old_fp;
  new_fp->a = new_a;
  asm("");
  gbl_foo = (struct foo *)new_fp;
  spin_unlock(&foo_mutex);
  synchronize_rcu();
}

// c::main
// file rcu_harness.c line 73
int main()
{
  foo1.a = 1;
  gbl_foo = &foo1;
  gbl_foo->a = 1;

//__CPROVER_ASYNC_1:
  pthread_t t1, t2;
  
  pthread_create(&t1, NULL, foo_update_a(2), NULL);
  //pthread_create(&t2, NULL, worker_2, NULL);
  //foo_update_a(2);
  pthread_join(t2, NULL);

  int a_value;
  a_value=foo_get_a();
  /* RCU correct */
  assert(a_value == 1 || a_value == 2);
}

// c::rcu_read_lock
// file linux-3.2.21/include/linux/rcupdate.h line 636
static void rcu_read_lock(void)
{
  __rcu_read_lock();
  // (void)0;

//__CPROVER_DUMP_L1:
  ;
}

// c::rcu_read_unlock
// file linux-3.2.21/include/linux/rcupdate.h line 658
static void rcu_read_unlock(void)
{

//__CPROVER_DUMP_L1:
//  ;
  // (void)0;
  __rcu_read_unlock();
}

// c::spin_lock
// file linux-3.2.21/include/linux/spinlock.h line 283
static void spin_lock(struct spinlock *lock)
{
  _raw_spin_lock(&lock->$anon0.rlock);
}

// c::spin_unlock
// file linux-3.2.21/include/linux/spinlock.h line 323
static void spin_unlock(struct spinlock *lock)
{
  __raw_spin_unlock(&lock->$anon0.rlock);
}

// c::synchronize_rcu
// file linux-3.2.21/include/linux/rcupdate.h line 163
static void synchronize_rcu(void)
{
  synchronize_sched();
}
