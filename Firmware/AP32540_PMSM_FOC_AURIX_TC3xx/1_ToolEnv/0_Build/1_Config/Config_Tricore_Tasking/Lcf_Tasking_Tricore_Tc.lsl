#define LCF_CSA0_SIZE 8k
#define LCF_USTACK0_SIZE 2k
#define LCF_ISTACK0_SIZE 1k

#define LCF_CSA1_SIZE 8k
#define LCF_USTACK1_SIZE 2k
#define LCF_ISTACK1_SIZE 1k

#define LCF_CSA2_SIZE 8k
#define LCF_USTACK2_SIZE 2k
#define LCF_ISTACK2_SIZE 1k

#define LCF_CSA3_SIZE 8k
#define LCF_USTACK3_SIZE 2k
#define LCF_ISTACK3_SIZE 1k

#define LCF_HEAP_SIZE  4k

#define LCF_CPU0 0
#define LCF_CPU1 1
#define LCF_CPU2 2
#define LCF_CPU3 3

/*Un comment one of the below statements to enable CpuX DMI RAM to hold global variables and functions*/
#define LCF_DEFAULT_HOST LCF_CPU0
/*#define LCF_DEFAULT_HOST LCF_CPU1*/
/*#define LCF_DEFAULT_HOST LCF_CPU2*/
/*#define LCF_DEFAULT_HOST LCF_CPU3*/

#define LCF_DSPR3_START 0x40000000
#define LCF_DSPR3_SIZE  96k

#define LCF_DSPR2_START 0x50000000
#define LCF_DSPR2_SIZE  96k

#define LCF_DSPR1_START 0x60000000
#define LCF_DSPR1_SIZE  240k

#define LCF_DSPR0_START 0x70000000
#define LCF_DSPR0_SIZE  240k

#define LCF_CSA3_OFFSET        (LCF_DSPR3_SIZE - 1k - LCF_CSA3_SIZE)
#define LCF_ISTACK3_OFFSET    (LCF_CSA3_OFFSET - 256 - LCF_ISTACK3_SIZE)
#define LCF_USTACK3_OFFSET    (LCF_ISTACK3_OFFSET - 256 - LCF_USTACK3_SIZE)

#define LCF_CSA2_OFFSET        (LCF_DSPR2_SIZE - 1k - LCF_CSA2_SIZE)
#define LCF_ISTACK2_OFFSET    (LCF_CSA2_OFFSET - 256 - LCF_ISTACK2_SIZE)
#define LCF_USTACK2_OFFSET    (LCF_ISTACK2_OFFSET - 256 - LCF_USTACK2_SIZE)

#define LCF_CSA1_OFFSET        (LCF_DSPR1_SIZE - 1k - LCF_CSA1_SIZE)
#define LCF_ISTACK1_OFFSET    (LCF_CSA1_OFFSET - 256 - LCF_ISTACK1_SIZE)
#define LCF_USTACK1_OFFSET    (LCF_ISTACK1_OFFSET - 256 - LCF_USTACK1_SIZE)

#define LCF_CSA0_OFFSET        (LCF_DSPR0_SIZE - 1k - LCF_CSA0_SIZE)
#define LCF_ISTACK0_OFFSET    (LCF_CSA0_OFFSET - 256 - LCF_ISTACK0_SIZE)
#define LCF_USTACK0_OFFSET    (LCF_ISTACK0_OFFSET - 256 - LCF_USTACK0_SIZE)

#define LCF_HEAP0_OFFSET    (LCF_USTACK0_OFFSET - LCF_HEAP_SIZE)
#define LCF_HEAP1_OFFSET    (LCF_USTACK1_OFFSET - LCF_HEAP_SIZE)
#define LCF_HEAP2_OFFSET    (LCF_USTACK2_OFFSET - LCF_HEAP_SIZE)
#define LCF_HEAP3_OFFSET    (LCF_USTACK3_OFFSET - LCF_HEAP_SIZE)

#define LCF_INTVEC0_START 0x802FE000
#define LCF_INTVEC1_START 0x805FE000
#define LCF_INTVEC2_START 0x808FE000
#define LCF_INTVEC3_START 0x809FE000

#define LCF_TRAPVEC0_START 0x80000100
#define LCF_TRAPVEC1_START 0x80300100
#define LCF_TRAPVEC2_START 0x80600100
#define LCF_TRAPVEC3_START 0x80900100

#define LCF_STARTPTR_CPU0 0x80000000
#define LCF_STARTPTR_CPU1 0x80300000
#define LCF_STARTPTR_CPU2 0x80600000
#define LCF_STARTPTR_CPU3 0x80900000

#define LCF_STARTPTR_NC_CPU0 0xA0000000
#define LCF_STARTPTR_NC_CPU1 0xA0300000
#define LCF_STARTPTR_NC_CPU2 0xA0600000
#define LCF_STARTPTR_NC_CPU3 0xA0900000

#define INTTAB0         (LCF_INTVEC0_START)
#define INTTAB1         (LCF_INTVEC1_START)
#define INTTAB2         (LCF_INTVEC2_START)
#define INTTAB3         (LCF_INTVEC3_START)

#define TRAPTAB0        (LCF_TRAPVEC0_START)
#define TRAPTAB1        (LCF_TRAPVEC1_START)
#define TRAPTAB2        (LCF_TRAPVEC2_START)
#define TRAPTAB3        (LCF_TRAPVEC3_START)

#define RESET LCF_STARTPTR_NC_CPU0

#include "tc1v1_6_2.lsl"

// Specify a multi-core processor environment (mpe)

processor mpe
{
    derivative = tc38;
}

derivative tc38
{
    core tc0
    {
        architecture = TC1V1.6.2;
        space_id_offset = 100;          // add 100 to all space IDs in the architecture definition
        copytable_space = vtc:linear;     // use the copy table in the virtual core for 'bss' and initialized data sections
    }
    
    core tc1 // core 1 TC16E
    {
        architecture = TC1V1.6.2;
        space_id_offset = 200;          // add 200 to all space IDs in the architecture definition
        copytable_space = vtc:linear;     // use the copy table in the virtual core for 'bss' and initialized data sections
    }
    
    core tc2 // core 2 TC16P
    {
        architecture = TC1V1.6.2;
        space_id_offset = 300;          // add 300 to all space IDs in the architecture definition
        copytable_space = vtc:linear;     // use the copy table in the virtual core for 'bss' and initialized data sections
    }
    
    core tc3 // core 3 TC16P
    {
        architecture = TC1V1.6.2;
        space_id_offset = 400;          // add 400 to all space IDs in the architecture definition
        copytable_space = vtc:linear;     // use the copy table in the virtual core for 'bss' and initialized data sections
    }
    
    core vtc
    {
        architecture = TC1V1.6.2;
        import tc0;                     // add all address spaces of core tc0 to core vtc for linking and locating
        import tc1;                     //                                tc1
        import tc2;                     //                                tc2
        import tc3;                     //                                tc3
    }
    
    bus sri
    {
        mau = 8;
        width = 32;
        
        // map shared addresses one-to-one to real cores and virtual core, segments starting from 0x0
        map (dest=bus:tc0:fpi_bus, src_offset=0, dest_offset=0, size=0x40000000);
        map (dest=bus:tc1:fpi_bus, src_offset=0, dest_offset=0, size=0x40000000);
        map (dest=bus:tc2:fpi_bus, src_offset=0, dest_offset=0, size=0x40000000);
        map (dest=bus:tc3:fpi_bus, src_offset=0, dest_offset=0, size=0x40000000);
        map (dest=bus:vtc:fpi_bus, src_offset=0, dest_offset=0, size=0x40000000);

        // map shared addresses one-to-one to real cores and virtual core, segments starting from 0x8
        map (dest=bus:tc0:fpi_bus, src_offset=0x80000000, dest_offset=0x80000000, size=0x40000000);
        map (dest=bus:tc1:fpi_bus, src_offset=0x80000000, dest_offset=0x80000000, size=0x40000000);
        map (dest=bus:tc2:fpi_bus, src_offset=0x80000000, dest_offset=0x80000000, size=0x40000000);
        map (dest=bus:tc3:fpi_bus, src_offset=0x80000000, dest_offset=0x80000000, size=0x40000000);
        map (dest=bus:vtc:fpi_bus, src_offset=0x80000000, dest_offset=0x80000000, size=0x40000000);

        // map shared addresses one-to-one to real cores and virtual core, segments starting from 0xe
        map (dest=bus:tc0:fpi_bus, src_offset=0xe0000000, dest_offset=0xe0000000, size=0x20000000);
        map (dest=bus:tc1:fpi_bus, src_offset=0xe0000000, dest_offset=0xe0000000, size=0x20000000);
        map (dest=bus:tc2:fpi_bus, src_offset=0xe0000000, dest_offset=0xe0000000, size=0x20000000);
        map (dest=bus:tc3:fpi_bus, src_offset=0xe0000000, dest_offset=0xe0000000, size=0x20000000);
        map (dest=bus:vtc:fpi_bus, src_offset=0xe0000000, dest_offset=0xe0000000, size=0x20000000);
        
        // map local memory
        map (dest=bus:tc0:fpi_bus, src_offset=0x70100000, dest_offset=0x70100000, size=0xff00000, exec_priority=2);
        map (dest=bus:tc0:fpi_bus, src_offset=0x70000000, dest_offset=0x70000000, size=0x00100000, priority=2, exec_priority=0);
        map (dest=bus:tc0:fpi_bus, src_offset=0x40000000, dest_offset=0x40000000, size=0x30000000);
        map (dest=bus:tc1:fpi_bus, src_offset=0x60000000, dest_offset=0x60000000, size=0x00100000, priority=2, exec_priority=0);
        map (dest=bus:tc1:fpi_bus, src_offset=0x60100000, dest_offset=0x60100000, size=0xff00000, exec_priority=2);
        map (dest=bus:tc1:fpi_bus, src_offset=0x40000000, dest_offset=0x40000000, size=0x20000000);
        map (dest=bus:tc1:fpi_bus, src_offset=0x70000000, dest_offset=0x70000000, size=0x10000000);
        map (dest=bus:tc2:fpi_bus, src_offset=0x50000000, dest_offset=0x50000000, size=0x00100000, priority=2, exec_priority=0);
        map (dest=bus:tc2:fpi_bus, src_offset=0x50100000, dest_offset=0x50100000, size=0xff00000, exec_priority=2);
        map (dest=bus:tc2:fpi_bus, src_offset=0x40000000, dest_offset=0x40000000, size=0x10000000);
        map (dest=bus:tc2:fpi_bus, src_offset=0x60000000, dest_offset=0x60000000, size=0x20000000);
        map (dest=bus:tc3:fpi_bus, src_offset=0x40000000, dest_offset=0x40000000, size=0x00100000, priority=2, exec_priority=0);
        map (dest=bus:tc3:fpi_bus, src_offset=0x40100000, dest_offset=0x40100000, size=0xff00000, exec_priority=2);
        map (dest=bus:tc3:fpi_bus, src_offset=0x50000000, dest_offset=0x50000000, size=0x30000000);
        map (dest=bus:vtc:fpi_bus, src_offset=0x40000000, dest_offset=0x40000000, size=0x40000000);
    }
    
    memory dsram3 // Data Scratch Pad Ram
    {
        mau = 8;
        size = 96k;
        type = ram;
        map  local (dest=bus:tc3:fpi_bus, dest_offset=0xd0000000, size=96k, priority=8);
        map global (dest=bus:sri, dest_offset=0x40000000, size=96k);
    }
    
    memory psram3 // Program Scratch Pad Ram
    {
        mau = 8;
        size = 64k;
        type = ram;
        map  local (dest=bus:tc3:fpi_bus, dest_offset=0xc0000000, size=64k, exec_priority=1);
        map global (dest=bus:sri, dest_offset=0x40100000, size=64k);
    }

    memory cpu3_dlmu
    {
        mau = 8;
        size = 64k;
        type = ram;
        map     cached (dest=bus:sri, dest_offset=0x90030000,           size=64k);
        map not_cached (dest=bus:sri, dest_offset=0xb0030000, reserved, size=64k);
    }

    memory pflash3
    {
        mau = 8;
        size = 1M;
        type = rom;
        map     cached (dest=bus:sri, dest_offset=0x80900000,           size=1M);
        map not_cached (dest=bus:sri, dest_offset=0xa0900000, reserved, size=1M);
    }
    
    memory dsram2 // Data Scratch Pad Ram
    {
        mau = 8;
        size = 96k;
        type = ram;
        map  local (dest=bus:tc2:fpi_bus, dest_offset=0xd0000000, size=96k, priority=8);
        map global (dest=bus:sri, dest_offset=0x50000000, size=96k);
    }
    
    memory psram2 // Program Scratch Pad Ram
    {
        mau = 8;
        size = 64k;
        type = ram;
        map  local (dest=bus:tc2:fpi_bus, dest_offset=0xc0000000, size=64k, exec_priority=1);
        map global (dest=bus:sri, dest_offset=0x50100000, size=64k);
    }
    
    memory cpu2_dlmu
    {
        mau = 8;
        size = 64k;
        type = ram;
        map     cached (dest=bus:sri, dest_offset=0x90020000,           size=64k);
        map not_cached (dest=bus:sri, dest_offset=0xb0020000, reserved, size=64k);
    }
    
    memory pflash2
    {
        mau = 8;
        size = 3M;
        type = rom;
        map     cached (dest=bus:sri, dest_offset=0x80600000,           size=3M);
        map not_cached (dest=bus:sri, dest_offset=0xa0600000, reserved, size=3M);
    }
    
    memory dsram1 // Data Scratch Pad Ram
    {
        mau = 8;
        size = 240k;
        type = ram;
        map  local (dest=bus:tc1:fpi_bus, dest_offset=0xd0000000, size=240k, priority=8);
        map global (dest=bus:sri, dest_offset=0x60000000, size=240k);
    }
    
    memory psram1 // Program Scratch Pad Ram
    {
        mau = 8;
        size = 64k;
        type = ram;
        map  local (dest=bus:tc1:fpi_bus, dest_offset=0xc0000000, size=64k, exec_priority=1);
        map global (dest=bus:sri, dest_offset=0x60100000, size=64k);
    }

    memory cpu1_dlmu
    {
        mau = 8;
        size = 64k;
        type = ram;
        map     cached (dest=bus:sri, dest_offset=0x90010000,           size=64k);
        map not_cached (dest=bus:sri, dest_offset=0xb0010000, reserved, size=64k);
    }
    
    memory pflash1
    {
        mau = 8;
        size = 3M;
        type = rom;
        map     cached (dest=bus:sri, dest_offset=0x80300000,           size=3M);
        map not_cached (dest=bus:sri, dest_offset=0xa0300000, reserved, size=3M);
    }
    
    memory dsram0 // Data Scratch Pad Ram
    {
        mau = 8;
        size = 240k;
        type = ram;
        map  local (dest=bus:tc0:fpi_bus, dest_offset=0xd0000000, size=240k, priority=8);
        map global (dest=bus:sri, dest_offset=0x70000000, size=240k);
    }
    
    memory psram0 // Program Scratch Pad Ram
    {
        mau = 8;
        size = 64k;
        type = ram;
        map  local (dest=bus:tc0:fpi_bus, dest_offset=0xc0000000, size=64k, exec_priority=1);
        map global (dest=bus:sri, dest_offset=0x70100000, size=64k);
    }

    memory cpu0_dlmu
    {
        mau = 8;
        size = 64k;
        type = ram;
        map     cached (dest=bus:sri, dest_offset=0x90000000,           size=64k);
        map not_cached (dest=bus:sri, dest_offset=0xb0000000, reserved, size=64k);
    }
    
    memory pflash0
    {
        mau = 8;
        size = 3M;
        type = rom;
        map     cached (dest=bus:sri, dest_offset=0x80000000,           size=3M);
        map not_cached (dest=bus:sri, dest_offset=0xa0000000, reserved, size=3M);
    }
    
    memory dflash0
    {
        mau = 8;
        size = 512K;
        type = reserved nvram;
        map (dest=bus:sri, dest_offset=0xaf000000, size=512K  );
    }
    
    memory ucb
    {
        mau = 8;
        size = 24k;
        type = rom;
        map (dest=bus:sri, dest_offset=0xaf400000, reserved, size=24k);
    }
    
    memory lmu0ram
    {
        mau = 8;
        size = 128K;
        type = ram;
        map     cached (dest=bus:sri, dest_offset=0x90040000,           size=128K);
        map not_cached (dest=bus:sri, dest_offset=0xb0040000, reserved, size=128K);
    }
    
#if (__VERSION__ >= 6003)    
    section_setup :vtc:linear
    {
        heap "heap" (min_size = (1k), fixed, align = 8);
    }    
#endif
    
    section_setup :vtc:linear
    {
        start_address
        (
            symbol = "_START"
        );
    }
    
    /*Section setup for the copy table*/
    section_setup :vtc:linear
    {
        copytable
        (
            align = 4,
            dest =  linear,
            table
            {
                symbol = "_lc_ub_table";
                space = :tc0:linear, :tc0:abs24, :tc0:abs18, :tc0:csa;
            },
            table
            {
                symbol = "_lc_ub_table_tc1";
                space = :tc1:linear, :tc1:abs24, :tc1:abs18, :tc1:csa;
            },
            table
            {
                symbol = "_lc_ub_table_tc2";
                space = :tc2:linear, :tc2:abs24, :tc2:abs18, :tc2:csa;
            },
            table
            {
                symbol = "_lc_ub_table_tc3";
                space = :tc3:linear, :tc3:abs24, :tc3:abs18, :tc3:csa;
            }
        );
    }

    /*Sections located at absolute fixed address*/
    section_layout :tc0:linear
    {
        /*Fixed memory Allocations for stack memories*/
        group ustack0(ordered, align = 8, run_addr = mem:dsram0[LCF_USTACK0_OFFSET])
        {
            reserved "ustack_tc0" (size = LCF_USTACK0_SIZE);
        }
        "__USTACK0":= sizeof(group:ustack0) > 0  ? "_lc_ue_ustack_tc0" : 0;
        "__USTACK0_END":="_lc_ub_ustack_tc0";
                
        group istack0(ordered, align = 8, run_addr = mem:dsram0[LCF_ISTACK0_OFFSET])
        {
            reserved "istack_tc0" (size = LCF_ISTACK0_SIZE);
        }
        "__ISTACK0":= sizeof(group:istack0) > 0  ? "_lc_ue_istack_tc0" : 0;
        "__ISTACK0_END":="_lc_ub_istack_tc0";
    }        

    section_layout :tc0:csa
    {
        /*Fixed memory Allocations for CSA*/
        group (ordered)
        {
            group (align = 8, attributes=rw, run_addr=mem:dsram0[LCF_CSA0_OFFSET]) 
                reserved "csa_tc0" (size = LCF_CSA0_SIZE);
            "__CSA0":=        "_lc_ub_csa_tc0";
            "__CSA0_END":=    "_lc_ue_csa_tc0";        
        }
    }

    section_layout :tc1:linear
    {
        /*Fixed memory Allocations for stack memories*/
        group ustack1(ordered, align = 8, run_addr = mem:dsram1[LCF_USTACK1_OFFSET])
        {
            reserved "ustack_tc1" (size = LCF_USTACK1_SIZE);
        }
        "__USTACK1":= sizeof(group:ustack1) > 1  ? "_lc_ue_ustack_tc1" : 1;
        "__USTACK1_END":="_lc_ub_ustack_tc1";
                
        group istack1(ordered, align = 8, run_addr = mem:dsram1[LCF_ISTACK1_OFFSET])
        {
            reserved "istack_tc1" (size = LCF_ISTACK1_SIZE);
        }
        "__ISTACK1":= sizeof(group:istack1) > 1  ? "_lc_ue_istack_tc1" : 1;
        "__ISTACK1_END":="_lc_ub_istack_tc1";
    }        

    section_layout :tc1:csa
    {
        /*Fixed memory Allocations for CSA*/
        group (ordered)
        {
            group (align = 8, attributes=rw, run_addr=mem:dsram1[LCF_CSA1_OFFSET]) 
                reserved "csa_tc1" (size = LCF_CSA1_SIZE);
            "__CSA1":=        "_lc_ub_csa_tc1";
            "__CSA1_END":=    "_lc_ue_csa_tc1";        
        }
    }

    section_layout :tc2:linear
    {
        /*Fixed memory Allocations for stack memories*/
        group ustack2(ordered, align = 8, run_addr = mem:dsram2[LCF_USTACK2_OFFSET])
        {
            reserved "ustack_tc2" (size = LCF_USTACK2_SIZE);
        }
        "__USTACK2":= sizeof(group:ustack2) > 2  ? "_lc_ue_ustack_tc2" : 2;
        "__USTACK2_END":="_lc_ub_ustack_tc2";
                
        group istack2(ordered, align = 8, run_addr = mem:dsram2[LCF_ISTACK2_OFFSET])
        {
            reserved "istack_tc2" (size = LCF_ISTACK2_SIZE);
        }
        "__ISTACK2":= sizeof(group:istack2) > 2  ? "_lc_ue_istack_tc2" : 2;
        "__ISTACK2_END":="_lc_ub_istack_tc2";
    }        

    section_layout :tc2:csa
    {
        /*Fixed memory Allocations for CSA*/
        group (ordered)
        {
            group (align = 8, attributes=rw, run_addr=mem:dsram2[LCF_CSA2_OFFSET]) 
                reserved "csa_tc2" (size = LCF_CSA2_SIZE);
            "__CSA2":=        "_lc_ub_csa_tc2";
            "__CSA2_END":=    "_lc_ue_csa_tc2";        
        }
    }

    section_layout :tc3:linear
    {
        /*Fixed memory Allocations for stack memories*/
        group ustack3(ordered, align = 8, run_addr = mem:dsram3[LCF_USTACK3_OFFSET])
        {
            reserved "ustack_tc3" (size = LCF_USTACK3_SIZE);
        }
        "__USTACK3":= sizeof(group:ustack3) > 3  ? "_lc_ue_ustack_tc3" : 3;
        "__USTACK3_END":="_lc_ub_ustack_tc3";
                
        group istack3(ordered, align = 8, run_addr = mem:dsram3[LCF_ISTACK3_OFFSET])
        {
            reserved "istack_tc3" (size = LCF_ISTACK3_SIZE);
        }
        "__ISTACK3":= sizeof(group:istack3) > 3  ? "_lc_ue_istack_tc3" : 3;
        "__ISTACK3_END":="_lc_ub_istack_tc3";
    }        

    section_layout :tc3:csa
    {
        /*Fixed memory Allocations for CSA*/
        group (ordered)
        {
            group (align = 8, attributes=rw, run_addr=mem:dsram3[LCF_CSA3_OFFSET]) 
                reserved "csa_tc3" (size = LCF_CSA3_SIZE);
            "__CSA3":=        "_lc_ub_csa_tc3";
            "__CSA3_END":=    "_lc_ue_csa_tc3";        
        }
    }

    section_layout :vtc:linear
    {
        #include        "base_address_groups.lsl"
        
        "_SMALL_DATA_TC0" := "_SMALL_DATA_";
        "_SMALL_DATA_TC1" := "_SMALL_DATA_";
        "_SMALL_DATA_TC2" := "_SMALL_DATA_";
        "_SMALL_DATA_TC3" := "_SMALL_DATA_";

        "_LITERAL_DATA_TC0" := "_LITERAL_DATA_";
        "_LITERAL_DATA_TC1" := "_LITERAL_DATA_";
        "_LITERAL_DATA_TC2" := "_LITERAL_DATA_";
        "_LITERAL_DATA_TC3" := "_LITERAL_DATA_";

        "_A8_DATA_TC0" := "_A8_DATA_";
        "_A8_DATA_TC1" := "_A8_DATA_";
        "_A8_DATA_TC2" := "_A8_DATA_";
        "_A8_DATA_TC3" := "_A8_DATA_";

        "_A9_DATA_TC0" := "_A9_DATA_";
        "_A9_DATA_TC1" := "_A9_DATA_";
        "_A9_DATA_TC2" := "_A9_DATA_";
        "_A9_DATA_TC3" := "_A9_DATA_";
    }

    section_layout :vtc:linear
    {
        /*Fixed memory Allocations for Start up code*/
        group (ordered)
        {
            group reset (run_addr=RESET)
            {
                select ".text.start";
            }
            group start_tc1 (run_addr=LCF_STARTPTR_NC_CPU1)
            {
                select "(.text.start_cpu1*)";
            }
            group start_tc2 (run_addr=LCF_STARTPTR_NC_CPU2)
            {
                select "(.text.start_cpu2*)";
            }
            group start_tc3 (run_addr=LCF_STARTPTR_NC_CPU3)
            {
                select "(.text.start_cpu3*)";
            }
            "__START0" := RESET;
            "__START1" := LCF_STARTPTR_NC_CPU1;
            "__START2" := LCF_STARTPTR_NC_CPU2;
            "__START3" := LCF_STARTPTR_NC_CPU3;
            "__ENABLE_INDIVIDUAL_C_INIT_CPU1" := 1; /* Not used */
            "__ENABLE_INDIVIDUAL_C_INIT_CPU1" := 1;
            "__ENABLE_INDIVIDUAL_C_INIT_CPU2" := 1;
            "__ENABLE_INDIVIDUAL_C_INIT_CPU3" := 1;
        }
        
        /*Fixed memory Allocations for Trap Vector Table*/
        group (ordered)
        {
            group trapvec_tc0 (align = 8, run_addr=LCF_TRAPVEC0_START)
            {
                section "trapvec_tc0" (size=0x100, attributes=rx, fill=0)
                {
                    select "(.text.traptab_cpu0*)";
                }
            }
            group trapvec_tc1 (align = 8, run_addr=LCF_TRAPVEC1_START)
            {
                section "trapvec_tc1" (size=0x100, attributes=rx, fill=0)
                {
                    select "(.text.traptab_cpu1*)";
                }
            }
            group trapvec_tc2 (align = 8, run_addr=LCF_TRAPVEC2_START)
            {
                section "trapvec_tc2" (size=0x100, attributes=rx, fill=0)
                {
                    select "(.text.traptab_cpu2*)";
                }
            }
            group trapvec_tc3 (align = 8, run_addr=LCF_TRAPVEC3_START)
            {
                section "trapvec_tc3" (size=0x100, attributes=rx, fill=0)
                {
                    select "(.text.traptab_cpu3*)";
                }
            }
            "__TRAPTAB_CPU0" := TRAPTAB0;
            "__TRAPTAB_CPU1" := TRAPTAB1;
            "__TRAPTAB_CPU2" := TRAPTAB2;
            "__TRAPTAB_CPU3" := TRAPTAB3;
        }
        
        /*Fixed memory Allocations for Interrupt Vector Table*/
        group (ordered)
        {
            group int_tab_tc0 (ordered)
            {
                #include "inttab0.lsl"
            }
            group int_tab_tc1 (ordered)
            {
                #include "inttab1.lsl"
            }
            group int_tab_tc2 (ordered)
            {
                #include "inttab2.lsl"
            }
            group int_tab_tc3 (ordered)
            {
                #include "inttab3.lsl"
            }
            
            "__INTTAB_CPU0" = (LCF_INTVEC0_START);
            "__INTTAB_CPU1" = (LCF_INTVEC1_START);
            "__INTTAB_CPU2" = (LCF_INTVEC2_START);
            "__INTTAB_CPU3" = (LCF_INTVEC3_START);
        }
        
        /*Fixed memory Allocations for BMHD*/
        group (ordered)
        {
            group  bmh_0_orig (run_addr=mem:ucb[0x0000])
            {
                select ".rodata.bmhd_0_orig";
            }
            group  bmh_1_orig (run_addr=mem:ucb[0x0200])
            {
                select ".rodata.bmhd_1_orig";
            }
            group  bmh_2_orig (run_addr=mem:ucb[0x0400])
            {
                select ".rodata.bmhd_2_orig";
            }
            group  bmh_3_orig (run_addr=mem:ucb[0x0600])
            {
                select ".rodata.bmhd_3_orig";
            }
            group  bmh_blank (run_addr=mem:ucb[0x0800])
            {
            }
            group  bmh_0_copy (run_addr=mem:ucb[0x1000])
            {
                select ".rodata.bmhd_0_copy";
            }
            group  bmh_1_copy (run_addr=mem:ucb[0x1200])
            {
                select ".rodata.bmhd_1_copy";
            }
            group  bmh_2_copy (run_addr=mem:ucb[0x1400])
            {
                select ".rodata.bmhd_2_copy";
            }
            group  bmh_3_copy (run_addr=mem:ucb[0x1600])
            {
                select ".rodata.bmhd_3_copy";
            }
        }
	    group noclear (ordered, align = 8, attributes=rw, run_addr = mem:dsram0)
    	{
        	select ".bss_noclear";
	    }
	    group (ordered, align = 8, attributes=rw, run_addr = mem:dsram0)
    	{
        	select "heap";
	    }
        /*Code Sections, selectable by toolchain*/
#        if LCF_DEFAULT_HOST == LCF_CPU0
        group (ordered, run_addr=mem:pflash0)
#        endif
#        if LCF_DEFAULT_HOST == LCF_CPU1
        group (ordered, run_addr=mem:pflash1)
#        endif
#        if LCF_DEFAULT_HOST == LCF_CPU2
        group (ordered, run_addr=mem:pflash2)
#        endif
#        if LCF_DEFAULT_HOST == LCF_CPU3
        group (ordered, run_addr=mem:pflash3)
#        endif
        {
            select "(.rodata|.rodata.*)";
            select "(.text|.text.*)";
        }
    }
}
        
/*Near Abbsolute Addressable Data Sections*/
section_setup mpe:vtc:abs18                        
{                                        
    modify input ( space = mpe:tc0:abs18 )                   
    {                                    
        select ".zdata.zdata_cpu0|.zdata.zdata_cpu0.*";
        select ".zbss.zbss_cpu0|.zbss.zbss_cpu0.*";
        select ".zrodata.Ifx_Ssw_Tc0.*";
        select ".zrodata.Cpu0_Main.*";
    }                                    
                                         
    modify input ( space = mpe:tc1:abs18 )                   
    {                                    
        select ".zdata.zdata_cpu1|.zdata.zdata_cpu1.*";
        select ".zbss.zbss_cpu1|.zbss.zbss_cpu1.*";
        select ".zrodata.Ifx_Ssw_Tc1.*";
        select ".zrodata.Cpu1_Main.*";
    }                                    
                                         
    modify input ( space = mpe:tc2:abs18 )                   
    {                                    
        select ".zdata.zdata_cpu2|.zdata.zdata_cpu2.*";
        select ".zbss.zbss_cpu2|.zbss.zbss_cpu2.*";
        select ".zrodata.Ifx_Ssw_Tc2.*";
        select ".zrodata.Cpu2_Main.*";
    }                                    
                                         
    modify input ( space = mpe:tc3:abs18 )                   
    {                                    
        select ".zdata.zdata_cpu3|.zdata.zdata_cpu3.*";
        select ".zbss.zbss_cpu3|.zbss.zbss_cpu3.*";
        select ".zrodata.Ifx_Ssw_Tc3.*";
        select ".zrodata.Cpu3_Main.*";
    }                                    
                                         
    modify input ( space = mpe:vtc:tc0_abs18|tc1_abs18|tc2_abs18|tc3_abs18 )       
    {                                    
        select ".zdata.lmuzdata";
        select ".zbss.lmuzbss";
        select "(.zdata|.zdata.*)";
        select "(.zbss|.zbss.*)";
    }                                    
}                                        
                                         
section_setup mpe:vtc:linear                        
{                                        
    modify input ( space = mpe:tc0:linear )                   
    {                                    
        select ".data.Ifx_Ssw_Tc0.*";
        select ".data.Cpu0_Main.*";
        select ".data.data_cpu0";
        select ".bss.Ifx_Ssw_Tc0.*";
        select ".bss.Cpu0_Main.*";
        select ".bss.bss_cpu0";
        select ".rodata.Ifx_Ssw_Tc0.*";
        select ".rodata.Cpu0_Main.*";
        select ".rodata.rodata_cpu0";
        select ".text.Ifx_Ssw_Tc0.*";
        select ".text.Cpu0_Main.*";
        select ".text.text_cpu0*";
    }                                    
                                         
    modify input ( space = mpe:tc1:linear )                   
    {                                    
        select ".data.Ifx_Ssw_Tc1.*";
        select ".data.Cpu1_Main.*";
        select ".data.data_cpu1";
        select ".bss.Ifx_Ssw_Tc1.*";
        select ".bss.Cpu1_Main.*";
        select ".bss.bss_cpu1";
        select ".rodata.Ifx_Ssw_Tc1.*";
        select ".rodata.Cpu1_Main.*";
        select ".rodata.rodata_cpu1";
        select ".text.Ifx_Ssw_Tc1.*";
        select ".text.Cpu1_Main.*";
        select ".text.text_cpu1*";
    }                                    

    modify input ( space = mpe:tc2:linear )                   
    {                                    
        select ".data.Ifx_Ssw_Tc2.*";
        select ".data.Cpu2_Main.*";
        select ".data.data_cpu2";
        select ".bss.Ifx_Ssw_Tc2.*";
        select ".bss.Cpu2_Main.*";
        select ".bss.bss_cpu2";
        select ".rodata.Ifx_Ssw_Tc2.*";
        select ".rodata.Cpu2_Main.*";
        select ".rodata.rodata_cpu2";
        select ".text.Ifx_Ssw_Tc2.*";
        select ".text.Cpu2_Main.*";
        select ".text.text_cpu2*";
    }                                    
    
    modify input ( space = mpe:tc3:linear )                   
    {                                    
        select ".data.Ifx_Ssw_Tc3.*";
        select ".data.Cpu3_Main.*";
        select ".data.data_cpu3";
        select ".bss.Ifx_Ssw_Tc3.*";
        select ".bss.Cpu3_Main.*";
        select ".bss.bss_cpu3";
        select ".rodata.Ifx_Ssw_Tc3.*";
        select ".rodata.Cpu3_Main.*";
        select ".rodata.rodata_cpu3";
        select ".text.Ifx_Ssw_Tc3.*";
        select ".text.Cpu3_Main.*";
        select ".text.text_cpu3*";
    }                                    

#if LCF_DEFAULT_HOST == LCF_CPU0
    modify input ( space = mpe:tc0:linear, copy )                   
#endif
#if LCF_DEFAULT_HOST == LCF_CPU1
    modify input ( space = mpe:tc1:linear, copy )                   
#endif
#if LCF_DEFAULT_HOST == LCF_CPU2
    modify input ( space = mpe:tc2:linear, copy )                   
#endif
#if LCF_DEFAULT_HOST == LCF_CPU3
    modify input ( space = mpe:tc3:linear, copy )                   
#endif
    {
        select ".data.*";
        select ".bss.*";
    }                                                           
}                                        

/*Relative A0/A1/A8/A9 Addressable Sections*/
section_setup mpe:vtc:abs24                        
{                                        
    modify input ( space = mpe:vtc:tc0_abs24|tc1_abs24|tc2_abs24|tc3_abs24 )       
    {                                    
        select "(.data_a0.sdata|.data_a0.sdata.*)";
        select "(.bss_a0.sbss|.bss_a0.sbss.*)";
        select "(.rodata_a1.srodata|.rodata_a1.srodata.*)";
        select "(.ldata|.ldata.*)";
        select "(.data_a9.a9sdata|.data_a9.a9sdata.*)";
        select "(.bss_a9.a9sbss|.bss_a9.a9sbss.*)";
        select "(.rodata_a8.a8srodata|.rodata_a8.a8srodata.*)";
    }                                    
}                                        
                                         
section_layout mpe:tc0:linear             
{                    
    /*Cpu specific SRAM Sections*/
    group (ordered, attributes=rw, run_addr = mem:mpe:dsram0)
    {
        select ".data.*";
        select ".bss.*";
    }     
    group (ordered, attributes=rw, run_addr = mem:mpe:psram0)
    {
        select "(.text.cpu0_psram|.text.cpu0_psram.*)";
        select "(.text.psram_text_cpu0|.text.psram_text_cpu0.*)";
    }     
    /*Cpu specific LMU Sections*/
    group (ordered, attributes=rw, run_addr = mem:mpe:cpu0_dlmu)
    {
        select "(.data.lmudata_cpu0|.data.lmudata_cpu0.*)";
        select "(.bss.lmubss_cpu0|.bss.lmubss_cpu0.*)";
    }     
    /*Cpu specific PFLASH Sections*/
    group (ordered, align = 4, run_addr=mem:mpe:pflash0)
    {
        select ".rodata.*";
        select ".text.*";
    }
}                    
      
section_layout mpe:tc1:linear             
{                    
    /*Cpu specific SRAM Sections*/
    group (ordered, attributes=rw, run_addr = mem:mpe:dsram1)
    {
        select ".data.*";
        select ".bss.*";
    }     
    group (ordered, attributes=rw, run_addr = mem:mpe:psram1)
    {
        select "(.text.cpu1_psram|.text.cpu1_psram.*)";
        select "(.text.psram_text_cpu1|.text.psram_text_cpu1.*)";
    }     
    /*Cpu specific LMU Sections*/
    group (ordered, attributes=rw, run_addr = mem:mpe:cpu1_dlmu)
    {
        select "(.data.lmudata_cpu1|.data.lmudata_cpu1.*)";
        select "(.bss.lmubss_cpu1|.bss.lmubss_cpu1.*)";
    }     
    /*Cpu specific PFLASH Sections*/
    group (ordered, align = 4, run_addr=mem:mpe:pflash1)
    {
        select ".rodata.*";
        select ".text.*";
    }
}                    
      
section_layout mpe:tc2:linear             
{                    
    /*Cpu specific SRAM Sections*/
    group (ordered, attributes=rw, run_addr = mem:mpe:dsram2)
    {
        select ".data.*";
        select ".bss.*";
    }     
    group (ordered, attributes=rw, run_addr = mem:mpe:psram2)
    {
        select "(.text.cpu2_psram|.text.cpu2_psram.*)";
        select "(.text.psram_text_cpu2|.text.psram_text_cpu2.*)";
    }     
    /*Cpu specific LMU Sections*/
    group (ordered, attributes=rw, run_addr = mem:mpe:cpu2_dlmu)
    {
        select "(.data.lmudata_cpu2|.data.lmudata_cpu2.*)";
        select "(.bss.lmubss_cpu2|.bss.lmubss_cpu2.*)";
    }     
    /*Cpu specific PFLASH Sections*/
    group (ordered, align = 4, run_addr=mem:mpe:pflash2)
    {
        select ".rodata.*";
        select ".text.*";
    }
}                    
      
section_layout mpe:tc3:linear             
{                    
    /*Cpu specific SRAM Sections*/
    group (ordered, attributes=rw, run_addr = mem:mpe:dsram3)
    {
        select ".data.*";
        select ".bss.*";
    }     
    group (ordered, attributes=rw, run_addr = mem:mpe:psram3)
    {
        select "(.text.cpu3_psram|.text.cpu3_psram.*)";
        select "(.text.psram_text_cpu3|.text.psram_text_cpu3.*)";
    }     
    /*Cpu specific LMU Sections*/
    group (ordered, attributes=rw, run_addr = mem:mpe:cpu3_dlmu)
    {
        select "(.data.lmudata_cpu3|.data.lmudata_cpu3.*)";
        select "(.bss.lmubss_cpu3|.bss.lmubss_cpu3.*)";
    }     
    /*Cpu specific PFLASH Sections*/
    group (ordered, align = 4, run_addr=mem:mpe:pflash3)
    {
        select ".rodata.*";
        select ".text.*";
    }
}                    
      
