#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const char ____versions[]
__used __section("__versions") =
	"\x18\x00\x00\x00\xf0\x61\x8c\xfe"
	"_raw_read_lock\0\0"
	"\x20\x00\x00\x00\xdd\xb7\x9c\x61"
	"simple_read_from_buffer\0"
	"\x1c\x00\x00\x00\xb6\x55\x4d\xdd"
	"_raw_read_unlock\0\0\0\0"
	"\x1c\x00\x00\x00\xca\x39\x82\x5b"
	"__x86_return_thunk\0\0"
	"\x18\x00\x00\x00\x41\xfe\x8e\xe6"
	"_raw_write_lock\0"
	"\x20\x00\x00\x00\x66\x47\x4f\xbb"
	"simple_write_to_buffer\0\0"
	"\x1c\x00\x00\x00\x98\x5c\x23\x40"
	"_raw_write_unlock\0\0\0"
	"\x10\x00\x00\x00\x38\xdf\xac\x69"
	"memcpy\0\0"
	"\x10\x00\x00\x00\x9c\x53\x4d\x75"
	"strlen\0\0"
	"\x18\x00\x00\x00\x8c\x89\xd4\xcb"
	"fortify_panic\0\0\0"
	"\x10\x00\x00\x00\x94\xb6\x16\xa9"
	"strnlen\0"
	"\x10\x00\x00\x00\x7e\x3a\x2c\x12"
	"_printk\0"
	"\x1c\x00\x00\x00\xea\x0a\x92\x2f"
	"__register_chrdev\0\0\0"
	"\x14\x00\x00\x00\xc2\xde\x7b\x8e"
	"proc_create\0"
	"\x14\x00\x00\x00\x66\xe4\x4b\xf9"
	"kernel_kobj\0"
	"\x20\x00\x00\x00\x6a\x9b\x69\x64"
	"kobject_create_and_add\0\0"
	"\x1c\x00\x00\x00\x7c\x87\x2d\xee"
	"sysfs_create_group\0\0"
	"\x14\x00\x00\x00\x6c\x9c\xd7\x73"
	"kobject_put\0"
	"\x1c\x00\x00\x00\xc0\xfb\xc3\x6b"
	"__unregister_chrdev\0"
	"\x14\x00\x00\x00\xbb\x98\x3b\x46"
	"proc_remove\0"
	"\x14\x00\x00\x00\xbb\x6d\xfb\xbd"
	"__fentry__\0\0"
	"\x18\x00\x00\x00\x76\xf2\x0f\x5e"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "219DA0ECBA4B30CA2F223BD");
