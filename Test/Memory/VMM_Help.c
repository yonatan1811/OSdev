
//****************************************************************************
//**
//**		-Page Table Entries (PTE). This provides an abstract interface
//**		to aid in management of PTEs.
//**

#include "VMM_Help.h"


//just some simple functions to modify and edit the pages

inline void pt_entry_add_attrib (pt_entry* e, uint32_t attrib) {
	*e |= attrib;
}

inline void pt_entry_del_attrib (pt_entry* e, uint32_t attrib) {
	*e &= ~attrib;
}

inline void pt_entry_set_frame (pt_entry* e, physical_addr addr) {
	*e = (*e & ~I86_PTE_FRAME) | addr;
}

inline bool pt_entry_is_present (pt_entry e) {
	return e & I86_PTE_PRESENT;
}

inline bool pt_entry_is_writable (pt_entry e) {
	return e & I86_PTE_WRITABLE;
}

inline physical_addr pt_entry_pfn (pt_entry e) {
	return e & I86_PTE_FRAME;
}


//************************//
//functions for the page directory table:

inline void pd_entry_add_attrib (pd_entry* e, uint32_t attrib) {
	*e |= attrib;
}

inline void pd_entry_del_attrib (pd_entry* e, uint32_t attrib) {
	*e &= ~attrib;
}

inline void pd_entry_set_frame (pd_entry* e, physical_addr addr) {
	*e = (*e & ~I86_PDE_FRAME) | addr;
}

inline bool pd_entry_is_present (pd_entry e) {
	return e & I86_PDE_PRESENT;
}

inline bool pd_entry_is_writable (pd_entry e) {
	return e & I86_PDE_WRITABLE;
}

inline physical_addr pd_entry_pfn (pd_entry e) {
	return e & I86_PDE_FRAME;
}

inline bool pd_entry_is_user (pd_entry e) {
	return e & I86_PDE_USER;
}

inline bool pd_entry_is_4mb (pd_entry e) {
	return e & I86_PDE_4MB;
}
