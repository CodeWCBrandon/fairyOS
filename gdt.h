#ifndef __GDT_H
#define __GDT_H
#include "types.h"

    class GlobalDescriptorTable
    {
        public:
            //For the Entries
            class SegmentDescriptor
            {
                private:
                    uint16_t limit_lo; // limit or size low byte 
                    uint16_t base_lo; //  pointer low byte
                    uint8_t base_hi; // pointer high byte
                    uint8_t type; //access rights
                    uint8_t limit_hi; //limit or size high byte
                    uint8_t flags_limit_hi; //flags high byte
                    uint8_t base_vhi; //second pointer high byte

                public:
                    //constructor for each segment
                    SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type, uint8_t types);
                    uint32_t Base();
                    uint32_t Limit();

            } __attribute__((packed));

            SegmentDescriptor nullSegmentSelector; // empty segment for template
            SegmentDescriptor unusedSegmentSelector; 
            SegmentDescriptor codeSegmentSelector; // code segment
            SegmentDescriptor dataSegmentSelector; // data segment
        
            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            uint16_t codeSegmentSelector(); // offset code segment
            uint16_t dataSegmentSelector(); // offset data segment
    };

#endif