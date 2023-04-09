/**
* @File ldr_type.h
* @Date 2023-04-02
* @Description 机器相关信息结构
* @Author Ticks
* @Email ticks.cc\@gmail.com
*
* Copyright 2023 Ticks, Inc. All rights reserved. 
**/

#ifndef __BEETLE_OS_INIT_LDR_LDR_TYPE_H
#define __BEETLE_OS_INIT_LDR_LDR_TYPE_H

#include "vga_str.h"

namespace _Ldr {

#define BFH_RW_R 1
#define BFH_RW_W 2

#define BFH_BUF_SZ 0x1000
#define BFH_ONERW_SZ 0x1000
#define BFH_RWONE_OK 1
#define BFH_RWONE_ER 2
#define BFH_RWALL_OK 3

/*-----------------------------------------------------------------*/

#define IMAGE_OS_FILE_NAME_MAX 192  // 映像文件内部文件名最大大小
#define IMAGE_OS_FHD_COUNT_MAX 256  // 映像文件头最大数量
#define IMAGE_OS_MDC_END_MAGIC  0xaaffaaffaaffaaff  // 映像文件结束标识
#define IMAGE_OS_MDC_RV_MAGIC   0xffaaffaaffaaffaa  // 映像文件version和magic
#define IMAGE_OS_HDC_OFF (0x1000)
#define IMAGE_FILE_PHY_ADDR 0x4000000           // 操作系统镜像物理地址
#define IMAGE_KERNEL_PHY_ADDR 0x2000000         // 内核映像文件存放物理地址 (32MB)
#define LDR_FILE_ADDR IMAGE_FILE_PHY_ADDR       // ldr 文件地址
#define MRD_DSC_ADDR (LDR_FILE_ADDR+0x1000)     // 映像文件

#define IMAGE_LDR_READ_INT_PHY_ADDR 0x1000      // ldr 文件物理内存地址
#define IMAGE_LDR_KERNEL_PHY_ADDR   0x200000    // ldr kernel 文件物理内存地址
#define IMGSHEL_PHYADR 0x30000
#define KERNEL_STACK_PHY_ADDR   (0x90000-0x10)  // 内核栈物理空间地址
#define KERNEL_STACK_SIZE       0x1000          // 内核栈大小 4KB
#define KERNEL_INIT_PAGE_PHY_ADDR 0x1000000     // 内核初始化MMU页表物理地址
#define KERNEL_INIT_FRVM_PHY_ADDR 0x800000
#define KERNEL_INIT_FRVM_SIZE   0x400000

/*-----------------------------------------------------------------*/

#define KRNL_VIRTUAL_ADDRESS_START 0xffff800000000000
#define KPML4_P (1<<0)
#define KPML4_RW (1<<1)
#define KPML4_US (1<<2)
#define KPML4_PWT (1<<3)
#define KPML4_PCD (1<<4)
#define KPML4_A (1<<5)

#define KPDPTE_P (1<<0)
#define KPDPTE_RW (1<<1)
#define KPDPTE_US (1<<2)
#define KPDPTE_PWT (1<<3)
#define KPDPTE_PCD (1<<4)
#define KPDPTE_A (1<<5)

#define KPDE_P (1<<0)
#define KPDE_RW (1<<1)
#define KPDE_US (1<<2)
#define KPDE_PWT (1<<3)
#define KPDE_PCD (1<<4)
#define KPDE_A (1<<5)
#define KPDE_D (1<<6)
#define KPDE_PS (1<<7)
#define KPDE_G (1<<8)
#define KPDE_PAT (1<<12)

#define KPML4_SHIFT 39
#define KPDPTTE_SHIFT 30
#define KPDP_SHIFT 21
#define PGENTY_SIZE 512

/*-----------------------------------------------------------------*/

#define ETYBAK_ADDR 0x2000
#define PM32_EIP_OFF (ETYBAK_ADDR)
#define PM32_ESP_OFF (ETYBAK_ADDR+4)
#define RM16_EIP_OFF (ETYBAK_ADDR+8)
#define RM16_ESP_OFF (ETYBAK_ADDR+12)

#define RWHDPACK_ADDR (ETYBAK_ADDR+32)
#define E820MAP_NR (ETYBAK_ADDR+64)          // 存放 e820 内存结构数量地址
#define E820MAP_ADDR_ADDR (ETYBAK_ADDR+68)
#define E820MAP_ADDR (0x5000)
#define VBE_INFO_ADDR (0x6000)
#define VBEM_INFO_ADDR (0x6400)

#define READHD_BUF_ADDR 0x3000

/*-----------------------------------------------------------------*/

#define MACH_INFO_ADDR (0x100000)
#define VBE_DISPI_IOPORT_INDEX (0x01CE)
#define VBE_DISPI_IOPORT_DATA (0x01CF)
#define VBE_DISPI_INDEX_ID (0)
#define VBE_DISPI_INDEX_XRES (1)
#define VBE_DISPI_INDEX_YRES (2)
#define VBE_DISPI_INDEX_BPP (3)
#define VBE_DISPI_INDEX_ENABLE (4)
#define VBE_DISPI_INDEX_BANK (5)
#define VBE_DISPI_INDEX_VIRT_WIDTH (6)
#define VBE_DISPI_INDEX_VIRT_HEIGHT (7)
#define VBE_DISPI_INDEX_X_OFFSET (8)
#define VBE_DISPI_INDEX_Y_OFFSET (9)
#define BGA_DEV_ID0 (0xB0C0) //- setting X and Y resolution and bit depth (8 BPP only), banked mode
#define BGA_DEV_ID1 (0xB0C1) //- virtual width and height, X and Y offset0
#define BGA_DEV_ID2 (0xB0C2) //- 15, 16, 24 and 32 BPP modes, support for linear frame buffer, support for retaining memory contents on mode switching
#define BGA_DEV_ID3 (0xB0C3) //- support for getting capabilities, support for using 8 bit DAC
#define BGA_DEV_ID4 (0xB0C4) //- VRAM increased to 8 MB
#define BGA_DEV_ID5 (0xB0C5) //- VRAM increased to 16 MB? [TODO: verify and check for other changes]
#define VBE_DISPI_BPP_4 (0x04)
#define VBE_DISPI_BPP_8 (0x08)
#define VBE_DISPI_BPP_15 (0x0F)
#define VBE_DISPI_BPP_16 (0x10)
#define VBE_DISPI_BPP_24 (0x18)
#define VBE_DISPI_BPP_32 (0x20)
#define VBE_DISPI_DISABLED (0x00)
#define VBE_DISPI_ENABLED (0x01)
#define VBE_DISPI_LFB_ENABLED (0x40)

/*-----------------------------------------------------------------*/

    // BIOS中断
    __NO_MANGLE void __REG_CALL(3) real_addr_call_entry(u16_t call_int, u16_t val1, u16_t val2);

    /*
     * 内核文件不止一个，为了让 Grub 只加载一个文件，
     * 选择将多个 bin 文件连接在一起，并在文件头部加上 4KB GRUB 头和各个文件的文件头描述符，
     * 结构类似下面这样：
     *
     * |-------------------|
     * |   4KB GRUB文件头   |
     * |-------------------|
     * |   映像文件头描述符   |
     * |   文件 1 头描述符   |
     * |   文件 2 头描述符   |
     * |   文件 3 头描述符   |
     * |       ....        |
     * |-------------------|
     * |     文件 1 内容     |
     * |     文件 2 内容     |
     * |     文件 3 内容     |
     * |       ....        |
     * |-------------------|
     *
     */

    // 映像文件内文件头描述符
    struct ImageOSFileHDes {
        u64_t type;             // 文件类型
        u64_t subtype;          // 文件子类型
        u64_t states;           // 文件状态
        u64_t header_id;        // 文件文件头ID
        u64_t offset_start;     // 在映像文件中开始偏移
        u64_t offset_end;       // 在映像文件中结束偏移
        u64_t file_real_size;   // 文件实际大小
        u64_t file_sum;         // 文件校验和
        char_t file_name[IMAGE_OS_FILE_NAME_MAX];   // 文件名称

    }; // ImageOSFileHDes

    // 映像文件头描述符
    struct ImageFileHDes {
        u64_t start_magic;          // 映像文件标识
        u64_t sf_checksum;          // 未使用
        u64_t sfs_offset;           // 未使用
        u64_t sfe_offset;           // 未使用
        u64_t sf_real_size;         // 未使用
        u64_t ldr_file_start;       // 二级引导器在映像文件中开始偏移
        u64_t ldr_file_end;         // 二级引导器在映像文件中结束偏移
        u64_t ldr_file_real_size;   // 二级引导器在映像文件中实际大小
        u64_t ldr_file_checksum;    // 二级引导器文件校验和
        u64_t fhd_start_offset;     // 文件头描述开始偏移
        u64_t fhd_end_offset;       // 文件头描述结束偏移
        u64_t fhd_real_size;        // 文件头描述实际大小
        u64_t fhd_checksum;         // 文件头描述校验和
        u64_t file_start_offset;    // 文件部分开始偏移
        u64_t file_end_offset;      // 文件部分结束偏移
        u64_t file_real_size;       // 文件部分实际大小
        u64_t file_checksum;        // 文件部分校验和
        u64_t ldr_fhd_index;        // 二级引导器在文件头描述中的序号
        u64_t fhd_count;            // 文件头描述符个数
        u64_t file_count;           // 文件个数
        u64_t end_magic;            // 结束标识
        u64_t version;              // 版本

    public:

    }; // ImageFileHDes

#define RLINTNR(x) (x*2)

    struct dpt_t {
        u8_t dp_bmgic;
        u8_t dp_pshead;
        u8_t dp_pssector;
        u8_t dp_pscyder;
        u8_t dp_ptype;
        u8_t dp_pehead;
        u8_t dp_pesector;
        u8_t dp_pecyder;
        u32_t dp_pslba;
        u32_t dp_plbasz;

    }__TYPE_ALIGN;


    struct mbr_t {
        char_t mb_byte[446];
        dpt_t mb_part[4];
        u16_t mb_endmgic;
    }__TYPE_ALIGN;

    struct ebr_t {
        char_t eb_byte[446];
        dpt_t eb_part[4];
        u16_t eb_endmgic;
    }__TYPE_ALIGN;

    struct idtr_t {
        u16_t idtlen;
        u32_t idtbas;
    };


    struct rwhdpach_t {

        u8_t rwhpk_sz;
        u8_t rwhpk_rv;
        u8_t rwhpk_sn;
        u8_t rwhpk_rv1;
        u16_t rwhpk_of;
        u16_t rwhpk_se;
        u32_t rwhpk_ll;
        u32_t rwhpk_lh;

    }__TYPE_ALIGN;

    /*
     * 标记 E820Map 内存类型
     */
#define E820_RAM_USABLE      1   // 可用内存
#define E820_RAM_RESERVED    2   // 保留内存
#define E820_RAM_ACPI_REC    3   // ACPI 表资源
#define E820_RAM_ACPI_NVS    4   // ACPI NVS 空间
#define E820_RAM_BAD_AREA    5   // 包含坏内存

    // E820 内存视图
    struct E820Map {
        u64_t start_addr;   /* 内存开始位置 */
        u64_t size;         /* 内存大小 */
        u32_t type;         /* 内存类型 */

    public:
        // 调用BIOS中断获取 e820 数组和数量
        static void MMap(_Base::Ptr<_Base::Ptr<E820Map>> _e820_map, _Base::Ptr<u32_t> _count);
        // 检查内存是否满足要求
        static _Base::Ptr<E820Map> CheckMemoryInE820MapCanUsable(
                _Base::Ptr<E820Map> _e820_map,
                u32_t _e820_count,
                u64_t _start_addr,
                u64_t _size
                );
        // 获取所有E820Map数组内存大小
        static u64_t GetAllMemorySize(_Base::CPtr<E820Map> _e820_map, u32_t _count);

    }__TYPE_ALIGN; // E820Map


    struct VBEInfo {
        char vbesignature[4];
        u16_t vbeversion;
        u32_t oemstringptr;
        u32_t capabilities;
        u32_t videomodeptr;
        u16_t totalmemory;
        u16_t oemsoftwarerev;
        u32_t oemvendornameptr;
        u32_t oemproductnameptr;
        u32_t oemproductrevptr;
        u8_t reserved[222];
        u8_t oemdata[256];
    }__TYPE_ALIGN;

    struct VBEomInfo {
        u16_t ModeAttributes;
        u8_t WinAAttributes;
        u8_t WinBAttributes;
        u16_t WinGranularity;
        u16_t WinSize;
        u16_t WinASegment;
        u16_t WinBSegment;
        u32_t WinFuncPtr;
        u16_t BytesPerScanLine;
        u16_t XResolution;
        u16_t YResolution;
        u8_t XCharSize;
        u8_t YCharSize;
        u8_t NumberOfPlanes;
        u8_t BitsPerPixel;
        u8_t NumberOfBanks;
        u8_t MemoryModel;
        u8_t BankSize;
        u8_t NumberOfImagePages;
        u8_t Reserved;
        u8_t RedMaskSize;
        u8_t RedFieldPosition;
        u8_t GreenMaskSize;
        u8_t GreenFieldPosition;
        u8_t BlueMaskSize;
        u8_t BlueFieldPosition;
        u8_t RsvdMaskSize;
        u8_t RsvdFieldPosition;
        u8_t DirectColorModeInfo;
        u32_t PhysBasePtr;
        u32_t Reserved1;
        u16_t Reserved2;
        u16_t LinBytesPerScanLine;
        u8_t BnkNumberOfImagePages;
        u8_t LinNumberOfImagePages;
        u8_t LinRedMaskSize;
        u8_t LinRedFieldPosition;
        u8_t LinGreenMaskSize;
        u8_t LinGreenFieldPosition;
        u8_t LinBlueMaskSize;
        u8_t LinBlueFieldPosition;
        u8_t LinRsvdMaskSize;
        u8_t LinRsvdFieldPosition;
        u32_t MaxPixelClock;
        u8_t Reserved3[189];

    }__TYPE_ALIGN; // 255

    struct Pixel {
        u8_t b;
        u8_t g;
        u8_t r;
        u8_t a;
    }__TYPE_ALIGN; // 4

#define RGBA(r, g, b) ((0|(r<<16)|(g<<8)|b))
    typedef u32_t pixel_t;
#define VBE_MODE 1
#define GPU_MODE 2
#define BGA_MODE 3

    struct GraphInfo {
        u32_t mode;
        u32_t x;
        u32_t y;
        u32_t gh_framphyadr;
        u32_t gh_onepixbits;
        u32_t gh_vbemodenr;
        u32_t gh_vifphyadr;
        u32_t gh_vmifphyadr;
        u32_t gh_bank;
        u32_t gh_curdipbnk;
        u32_t gh_nextbnk;
        u32_t gh_banksz;
        u32_t gh_logophyadrs;
        u32_t gh_logophyadre;
        u32_t gh_fontadr;
        u32_t gh_ftsectadr;
        u32_t gh_ftsectnr;
        u32_t gh_fnthight;
        u32_t gh_nxtcharsx;
        u32_t gh_nxtcharsy;
        u32_t gh_linesz;
        VBEInfo vbe_info;
        VBEomInfo vm_info;

    }__TYPE_ALIGN;

    struct bmfhead_t {
        u16_t bf_tag;   //0x4d42
        u32_t bf_size;
        u16_t bf_resd1;
        u16_t bf_resd2;
        u32_t bf_off;
    }__TYPE_ALIGN; //14

    struct bitminfo_t {
        u32_t bi_size;
        s32_t bi_w;
        s32_t bi_h;
        u16_t bi_planes;
        u16_t bi_bcount;
        u32_t bi_comp;
        u32_t bi_szimg;
        s32_t bi_xpelsper;
        s32_t bi_ypelsper;
        u32_t bi_clruserd;
        u32_t bi_clrimport;
    }__TYPE_ALIGN; // 40

    struct bmdbgr_t {
        u8_t bmd_b;
        u8_t bmd_g;
        u8_t bmd_r;
    }__TYPE_ALIGN;

    struct utf8_t {
        u8_t utf_b1;
        u8_t utf_b2;
        u8_t utf_b3;
        u8_t utf_b4;
        u8_t utf_b5;
        u8_t utf_b6;
    }__TYPE_ALIGN;

    struct fontfhder_t {
        u8_t fh_mgic[4];
        u32_t fh_fsize;
        u8_t fh_sectnr;
        u8_t fh_fhght;
        u16_t fh_wcpflg;
        u16_t fh_nchars;
        u8_t fh_rev[2];
    }__TYPE_ALIGN;

    struct ftsectif_t {
        u16_t fsf_fistuc;
        u16_t fsf_lastuc;
        u32_t fsf_off;
    }__TYPE_ALIGN;

    struct uftindx_t {
        u32_t ui_choff: 26;
        u32_t ui_chwith: 6;
    }__TYPE_ALIGN;

#define MAX_CHARBITBY 32
    struct fntdata_t {
        u8_t fntwxbyte;
        u8_t fnthx;
        u8_t fntwx;
        u8_t fntchmap[MAX_CHARBITBY];
    }__TYPE_ALIGN;


    struct klfocpymblk_t {
        u64_t sphyadr;
        u64_t ocymsz;
    }__TYPE_ALIGN;
#define MBS_MIGC (u64_t)((((u64_t)'L')<<56)|(((u64_t)'M')<<48)|(((u64_t)'O')<<40)|(((u64_t)'S')<<32)|(((u64_t)'M')<<24)|(((u64_t)'B')<<16)|(((u64_t)'S')<<8)|((u64_t)'P'))



#define BIOS_ACPI_RSDP_ADDR (0x40E)                     // BIOS ACPI RSDP 第一个查找位置
#define BIOS_ACPI_RSDP_AREA (1024)                      // BIOS ACPI RSDP 第一个查找区域
#define BIOS_ACPI_RSDP_OTHER_ADDR (0xE0000)             // BIOS ACPI RSDP 第二个查找位置
#define BIOS_ACPI_RSDP_OTHER_AREA (0xFFFFF - 0xE0000)   // BIOS ACPI RSDP 第二个查找区域

    // 设备ACPI信息表(RSDP(Root System Description Pointer) -> 根系统说明指针
    /*
     * 对于基于 Legacy BIOS 的系统而言，RSDP 表所在的物理地址并不固定，
     * 要么位于 EBDA（Extended BIOS Data Area）（位于物理地址 0x40E ）的前 1KB 范围内；
     * 要么位于 0x000E0000 到 0x000FFFFF 的物理地址范围内。
     * 内核在启动的时候，需要去这两个物理地址范围，通过遍历物理地址空间的方法寻找 RSDP 表，
     * 即通过寻找 RSDP 表的 Signature（RSD PTR）来定位 RSDP 的位置，
     * 并通过该表的 length 和 checksum 来确保找到的表是正确的。
     *
     * 对于基于UEFI的系统而言，RSDP Table 位于 EFI_SYSTEM_TABLE 。
     *
     * 结构参考 ACPI spc 设计
     *
     * RSDP ----> [RSD Table]
     *            [    |    ]
     *            [RSD Entry] -----> [XSD Table]
     *            [    |    ]        [    |    ]
     *            [RSD Entry]        [XSD Entry] -----> [  Sig  ]
     *            [   ...   ]        [    |    ]        [Content]
     *                               [XSD Entry]
     *                               [   ...   ]
     *
     * 参考资料 [1](https://uefi.org/htmlspecs/ACPI_Spec_6_4_html/05_ACPI_Software_Programming_Model/ACPI_Software_Programming_Model.html#root-system-description-pointer-rsdp)
     *
     */
    struct MachAcpiRsdp {
    public:
        u64_t sign;                 // ACPI表ID，唯一标识 (8 Bytes)
        u8_t checksum;              // 校验   (1 Byte)
        u8_t oem_id[6];             // OEM ID   (6 Bytes)
        u8_t revision;              // ReVision (1 Byte)
        u32_t rsd_table_phy_addr;   // RSD Table 物理地址 (4 Bytes)
        u32_t table_len;            // 表长度  (4 Bytes)
        u64_t xsd_table_phy_addr;   // XSD Table 物理地址 (8 Bytes)
        u8_t extended_checksum;     // Extended CheckSum    (1 Byte)
        u8_t reserved[3];           // Reserved (3 Byte)

    public:
        // 检查校验和
        static inline s32_t CheckSum(_Base::CPtr<MachAcpiRsdp> _rsdp)
        {
            s32_t sum = 0, table_len = s32_t(_rsdp->table_len);
            auto ap = _Base::Ptr<uchar_t>(_rsdp);
            while (table_len--) {
                sum += *ap++;
            }
            return (sum & 0xFF);
        }
        // 检查结构是否正确
        static inline _Base::Ptr<MachAcpiRsdp> CheckIsOk(_Base::Ptr<MachAcpiRsdp> _rsdp)
        {
            // revision 目前为 2
            if (nullptr == _rsdp || _rsdp->table_len == 0 || _rsdp->revision == 0) {
                return nullptr;
            }
            if (0 == CheckSum(_rsdp)) {
                return _rsdp;
            }
            return nullptr;
        }
        // 从 Extended BIOS Data Area 中查找 Rsdp
        static _Base::Ptr<MachAcpiRsdp> FindAcpiRsdpFromEbda();
        // 扫描指定内存，查看是否满足 Rsdp 结构要求
        static _Base::Ptr<MachAcpiRsdp> ScanRsdpFromEbda(_Base::Ptr<void> _addr, u32_t _size);

    }__TYPE_ALIGN;

    // 系统信息
    struct MachInfo {
    public:
        u64_t magic;              // LMOSMBSP //0
        u64_t checksum;           // 8
        u64_t kernel_stack_addr;  // 内核栈地址 16
        u64_t kernel_stack_size;  // 内核栈大小 24
        u64_t os_img_addr;        // 操作系统映像地址
        u64_t os_img_size;        // 操作系统映像大小
        u64_t kernel_img_addr;    // 内核映像地址
        u64_t kernel_img_size;    // 内核映像大小
        u64_t mb_krlvec;          //
        u64_t mb_krlrunmode;      //
        u64_t mb_kalldendpadr;    //
        u64_t mb_ksepadrs;        //
        u64_t mb_ksepadre;        //
        u64_t mb_kservadrs;       //
        u64_t mb_kservadre;       //
        u64_t next_free_phy_addr; // 下一个空闲的物理内存地址
        u64_t base_font_file_addr;// 操作系统字体文件地址
        u64_t base_font_file_size;// 操作系统字体文件大小
        u64_t vga_addr;           // 机器显存地址
        u64_t vga_size;           // 机器显存大小
        u64_t cpu_mode;           // 机器CPU工作模式
        u64_t memory_size;        // 机器内存大小
        u64_t e820_phy_addr;      // 机器e820数组地址
        u64_t e820_phy_count;     // 机器e820数组元素个数
        u64_t e820_phy_size;      // 机器e820数组大小
        u64_t mb_e820expadr;      //
        u64_t mb_e820exnr;        //
        u64_t mb_e820exsz;        //
        u64_t mb_memznpadr;       //
        u64_t mb_memznnr;         //
        u64_t mb_memznsz;         //
        u64_t mb_memznchksum;     //
        u64_t mb_memmappadr;      //
        u64_t mb_memmapnr;        //
        u64_t mb_memmapsz;        //
        u64_t mb_memmapchksum;    //
        u64_t mmu_page_phy_addr;  // 机器页表地址
        u64_t subpages_len;       // 机器页表个数
        u64_t phy_mem_map_size;   // 操作系统映射空间大小
        u64_t ebda_phy_addr;      // ebda 物理地址
        MachAcpiRsdp acpi_rsdp;   // ACPI RSDP表
        GraphInfo graph_info;     // 图形信息

    public:
        static _Base::Ptr<ImageOSFileHDes> GetOSFileHeaderDesByName(
                    _Base::Ptr<MachInfo> _info,
                    _Base::CPtr<char_t> _file_name);

    public:
        // 初始化系统信息结构
        static inline void Init(_Base::Ptr<MachInfo> _info)
        {
            _Base::memset(_info, 0, sizeof(MachInfo));
            _info->magic = MBS_MIGC;
        }

        // 初始化 Rsdp 并检查是否可用
        static void InitAcpiRsdp(_Base::Ptr<MachInfo> _info)
        {
            _info->ebda_phy_addr = BIOS_ACPI_RSDP_ADDR;
            auto rsdp = MachAcpiRsdp::FindAcpiRsdpFromEbda();
            if (nullptr == rsdp) {
                KError("Error: Your Computer isn't support ACPI");
            }
            // 拷贝到 MachInfo 结构体中
            _Base::memcopy(&(_info->acpi_rsdp), rsdp, sizeof(MachAcpiRsdp));
            // 拷贝后再次验证是否可用
            if (nullptr == MachAcpiRsdp::CheckIsOk(&_info->acpi_rsdp)) {
                KError("Error: Your Computer isn't support ACPI");
            }
        }

    }__TYPE_ALIGN; // MachInfo

}
#endif // __BEETLE_OS_INIT_LDR_LDR_TYPE_H
