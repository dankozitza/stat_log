// Created by cgo - DO NOT EDIT

package main

import "unsafe"

import "syscall"

type _ unsafe.Pointer

func _Cerrno(dst *error, x int32) { *dst = syscall.Errno(x) }
type _Ctype_void byte

