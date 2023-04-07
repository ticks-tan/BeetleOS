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

#include "kernel_base.h"
#include "base_string.h"

namespace _Ldr {

#define BFH_RW_R 1
#define BFH_RW_W 2

#define BFH_BUF_SZ 0x1000
#define BFH_ONERW_SZ 0x1000
#define BFH_RWONE_OK 1
#define BFH_RWONE_ER 2
#define BFH_RWALL_OK 3

/*-----------------------------------------------------------------*/

#define FHDSC_NMAX 192
#define FHDSC_SZMAX 256
#define MDC_END_GIC 0xaaffaaffaaffaaff
#define MDC_RVGIC 0xffaaffaaffaaffaa
#define REALDRV_PHY_ADDR 0x1000 // ldr 文件内存地址
#define ILDR_KERNEL_PHY_ADDR 0x200000   // ldr kernel 文件内存地址
#define IMGSHEL_PHYADR 0x30000
#define IKSTACK_PHYADR (0x90000-0x10)
#define IKSTACK_SIZE 0x1000
#define IMG_FILE_PHY_ADDR 0x4000000
#define IMGKRNL_PHYADR 0x2000000
#define KINITPAGE_PHYADR 0x1000000
#define KINITFRVM_PHYADR 0x800000
#define KINITFRVM_SZ 0x400000
#define LDR_FILE_ADDR IMG_FILE_PHY_ADDR    // ldr 文件地址
#define MLOSDSC_OFF (0x1000)
#define MRD_DSC_ADDR (LDR_FILE_ADDR+0x1000)    // 映像文件

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
#define E80MAP_NR (ETYBAK_ADDR+64)
#define E80MAP_ADDR_ADDR (ETYBAK_ADDR+68)
#define E80MAP_ADDR (0x5000)
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
    void __REG_CALL(3) real_addr_call_entry(u16_t call_int, u16_t val1, u16_t val2);

    struct fhdsc_t {
        u64_t fhd_type;
        u64_t fhd_subtype;
        u64_t fhd_stuts;
        u64_t fhd_id;
        u64_t fhd_intsfsoff;
        u64_t fhd_intsfend;
        u64_t fhd_frealsz;
        u64_t fhd_fsum;
        char_t fhd_name[FHDSC_NMAX];
    };

    struct mlosrddsc_t {
        u64_t mdc_mgic;
        u64_t mdc_sfsum;
        u64_t mdc_sfsoff;
        u64_t mdc_sfeoff;
        u64_t mdc_sfrlsz;
        u64_t mdc_ldrbk_s;
        u64_t mdc_ldrbk_e;
        u64_t mdc_ldrbk_rsz;
        u64_t mdc_ldrbk_sum;
        u64_t mdc_fhdbk_s;
        u64_t mdc_fhdbk_e;
        u64_t mdc_fhdbk_rsz;
        u64_t mdc_fhdbk_sum;
        u64_t mdc_filbk_s;
        u64_t mdc_filbk_e;
        u64_t mdc_filbk_rsz;
        u64_t mdc_filbk_sum;
        u64_t mdc_ldrcodenr;
        u64_t mdc_fhdnr;
        u64_t mdc_filnr;
        u64_t mdc_endgic;
        u64_t mdc_rv;
    };

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

#define RAM_USABLE 1
#define RAM_RESERV 2
#define RAM_ACPIREC 3
#define RAM_ACPINVS 4
#define RAM_AREACON 5

    struct E820Map {
        u64_t start_addr;   /* start of memory segment8 */
        u64_t size;         /* size of memory segment8 */
        u32_t type;         /* type of memory segment 4 */
    }__TYPE_ALIGN;


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

    struct mrsdp_t {
        u64_t rp_sign;
        u8_t rp_chksum;
        u8_t rp_oemid[6];
        u8_t rp_revn;
        u32_t rp_rsdtphyadr;
        u32_t rp_len;
        u64_t rp_xsdtphyadr;
        u8_t rp_echksum;
        u8_t rp_resv[3];
    }__TYPE_ALIGN;

    // 系统信息
    struct MachInfo {
        static inline void Init(_Base::Ptr<MachInfo> _info)
        {
            _Base::memset(_info, 0, sizeof(MachInfo));
            _info->magic = MBS_MIGC;
        }

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
        u64_t mb_nextwtpadr;      //
        u64_t base_font_file_addr;// 操作系统字体文件地址
        u64_t base_font_file_size;// 操作系统字体文件大小
        u64_t vga_addr;           // 机器显存地址
        u64_t vga_size;           // 机器显存大小
        u64_t cpu_mode;           // 机器CPU工作模式
        u64_t memory_size;        // 机器内存大小
        u64_t e820_addr;          // 机器e820数组地址
        u64_t e820_count;         // 机器e820数组元素个数
        u64_t e820_size;          // 机器e820数组大小
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
        u64_t mb_pml4padr;        // 机器页表地址
        u64_t mb_subpageslen;     // 机器页表个数
        u64_t mb_kpmapphymemsz;   // 操作系统映射空间大小
        u64_t mb_ebdaphyadr;      //
        mrsdp_t mb_mrsdp;           //
        GraphInfo graph_info;         // 图形信息
    }__TYPE_ALIGN;

}
#endif // __BEETLE_OS_INIT_LDR_LDR_TYPE_H
