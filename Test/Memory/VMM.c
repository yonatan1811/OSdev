#include "./VMM.h"
#include "./PMM.h"

bool vmmngr_alloc_page (pt_entry* e)
{
	//allocating a free physical frame
	void* p = pmmngr_alloc_block();//returns an address to the physical address of the frame.
	//now we need to add this to the page table.
	if(!p)
		return false;

	pt_entry_set_frame (e, (physical_addr)p); //setting the frame in the page table. e is a page table entry.
	pt_entry_add_attrib (e, I86_PTE_PRESENT);// setting the page as allocated.
	return true;
}

void vmmngr_free_page (pt_entry* e)
{
	void* p = (void*)pt_entry_pfn (*e); //getting the address of the frame.
	if (p)
		pmmngr_free_block (p); // freeing the frame from the physical memory manager.
 
	pt_entry_del_attrib (e, I86_PTE_PRESENT); //deleting the is present from the page table. so we can use it againg now.
}

inline pt_entry* vmmngr_ptable_lookup_entry (ptable* p,virtual_addr addr) {
 
	if (p)
		return &p->m_entries[ PAGE_TABLE_INDEX (addr) ];
	return 0;
}

inline pd_entry* vmmngr_pdirectory_lookup_entry (pdirectory* p, virtual_addr addr)
{
	if (p)
		return &p->m_entries[ PAGE_TABLE_INDEX (addr) ];
	return 0;
}


