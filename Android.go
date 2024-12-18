package libvisionpq_conditional_compile

import (
    "android/soong/android"
    "android/soong/cc"
    "fmt"
    "strings"
)

var SWPQ_SUPPORT_TARGET_PLATFORM = [...]string{
    "rk356x",
    "rk3588",
    "rk3576",
}

var HWPQ_SUPPORT_TARGET_PLATFORM = [...]string{
    "rk3576",
}

func init() {
    fmt.Println("librkswpq want to conditional Compile")
    android.RegisterModuleType("cc_librkswpq_prebuilt_library_shared", LibrkswpqFactory)
    fmt.Println("librkhwpq want to conditional Compile")
    android.RegisterModuleType("cc_librkhwpq_prebuilt_library_shared", LibrkhwpqFactory)
}

func LibrkswpqFactory() (android.Module) {
    module := cc.PrebuiltSharedLibraryFactory()
    android.AddLoadHook(module, LibrkswpqPrebuiltLibrary)
    return module
}

func LibrkhwpqFactory() (android.Module) {
    module := cc.PrebuiltSharedLibraryFactory()
    android.AddLoadHook(module, LibrkhwpqPrebuiltLibrary)
    return module
}

func LibrkswpqPrebuiltLibrary(ctx android.LoadHookContext) {
	type props struct {
        Multilib struct {
            Lib64 struct {
                Srcs []string
            }
            Lib32 struct {
                Srcs []string
            }
        }
        Export_include_dirs []string
    }
    p := &props{}

    p.Multilib.Lib64.Srcs = getSwpqLibrary(ctx, "arm64-v8a")
    p.Multilib.Lib32.Srcs = getSwpqLibrary(ctx, "armeabi-v7a")
    p.Export_include_dirs = getSwpqHeader(ctx)
    ctx.AppendProperties(p)
}

func LibrkhwpqPrebuiltLibrary(ctx android.LoadHookContext) {
	type props struct {
        Multilib struct {
            Lib64 struct {
                Srcs []string
            }
            Lib32 struct {
                Srcs []string
            }
        }
        Export_include_dirs []string
    }
    p := &props{}

    p.Multilib.Lib64.Srcs = getHwpqLibrary(ctx, "arm64-v8a")
    p.Multilib.Lib32.Srcs = getHwpqLibrary(ctx, "armeabi-v7a")
    p.Export_include_dirs = getHwpqHeader(ctx)
    ctx.AppendProperties(p)
}

func checkSwpqSupport(ctx android.LoadHookContext) bool {
    var soc string = getTargetSoc(ctx)
    for i := 0; i < len(SWPQ_SUPPORT_TARGET_PLATFORM); i++ {
        if (strings.EqualFold(SWPQ_SUPPORT_TARGET_PLATFORM[i], soc)) {
            fmt.Println("librkswpq enabled on " + soc)
            return true
        }
    }
    fmt.Println("librkswpq disabled on " + soc)
    return false
}

func checkHwpqSupport(ctx android.LoadHookContext) bool {
    var soc string = getTargetSoc(ctx)
    for i := 0; i < len(HWPQ_SUPPORT_TARGET_PLATFORM); i++ {
        if (strings.EqualFold(HWPQ_SUPPORT_TARGET_PLATFORM[i], soc)) {
            fmt.Println("librkhwpq enabled on " + soc)
            return true
        }
    }
    fmt.Println("librkhwpq disabled on " + soc)
    return false
}

func getSwpqLibrary(ctx android.LoadHookContext, arch string) ([]string) {
	var src []string
    var soc string = getTargetSoc(ctx)
    var prefix string = soc

    if (!checkSwpqSupport(ctx)) {
        prefix = "rk3576"
    }

    fmt.Println("soc=" + soc + " arch=" + arch)

    src = append(src,  "lib/Android/" + prefix + "/" + arch + "/librkswpq.so")

    return src
}

func getHwpqLibrary(ctx android.LoadHookContext, arch string) ([]string) {
	var src []string
    var soc string = getTargetSoc(ctx)
    var prefix string = soc

    if (!checkHwpqSupport(ctx)) {
        prefix = "rk3576"
    }

    fmt.Println("soc=" + soc + " arch=" + arch)

    src = append(src,  "lib/Android/" + prefix + "/" + arch + "/librkhwpq.so")

    return src
}

func getSwpqHeader(ctx android.LoadHookContext) ([]string) {
	var src []string
    var soc string = getTargetSoc(ctx)
    var prefix string = soc

    if (!checkSwpqSupport(ctx)) {
        prefix = "rk3576"
    }

    src = append(src, "lib/Android/" + prefix + "/include/")

    return src
}

func getHwpqHeader(ctx android.LoadHookContext) ([]string) {
	var src []string
    var soc string = getTargetSoc(ctx)
    var prefix string = soc

    if (!checkHwpqSupport(ctx)) {
        prefix = "rk3576"
    }

    src = append(src, "lib/Android/" + prefix + "/include/")

    return src
}

func getTargetSoc(ctx android.LoadHookContext) (string) {
    var target_board_platform string = ctx.AConfig().Getenv("TARGET_BOARD_PLATFORM")
    return target_board_platform
}

