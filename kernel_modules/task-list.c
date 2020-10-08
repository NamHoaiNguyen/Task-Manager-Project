#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include<linux/types.h>

char buffer[256];
char * get_task_state(long state)
{
    switch (state) {
        case TASK_RUNNING:
            return "TASK_RUNNING";
        case TASK_INTERRUPTIBLE:
            return "TASK_INTERRUPTIBLE";
        case TASK_UNINTERRUPTIBLE:
            return "TASK_UNINTERRUPTIBLE";
        case __TASK_STOPPED:
            return "__TASK_STOPPED";
        case __TASK_TRACED:
            return "__TASK_TRACED";
        default:
        {
            sprintf(buffer, "Unknown Type:%ld\n", state);
            return buffer;
        }
    }
}

static int test_tasks_init(void)
{
    struct task_struct *task_list, *test_list;
    struct mm_struct *m_area;
    struct thread_info info;
    struct list_head *p;
    unsigned int process_count = 0;
    pr_info("%s: In init\n", __func__);
    for_each_process(task_list) {
        pr_info("Process: %s\t PID:[%d]\t Processor:[%d]\t State:%s\n",
                task_list->comm, task_list->pid,
		task_list->cpu,
                get_task_state(task_list->state));
/*	list_for_each(p, &task_list->tasks) {
		test_list = list_entry(p, struct task_struct, tasks);
		pr_info ("Process: %s\t", test_list->comm);
	}
 
	info = task_list->thread_info;
	pr_info ("Cpu number: %d\t", info.flags);
*/

	m_area = task_list->mm;

	if (m_area != NULL) {
		pr_info("PGD of process: %lu", m_area->pgd);
	}

	if (m_area->owner = task_list) {
		pr_info("Giong nhau") ;
	}

	pr_info("Rlimit: %lu", task_list->signal->rlim[RLIMIT_DATA].rlim_cur); 

	process_count++;
    }
    pr_info("Number of processes:%u\n", process_count);
    return 0;
}

static void test_tasks_exit(void)
{
    pr_info("%s: In exit\n", __func__);
}

MODULE_LICENSE("GPL");
module_init(test_tasks_init);
module_exit(test_tasks_exit);
