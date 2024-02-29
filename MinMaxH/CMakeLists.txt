
add_library(
        MinMaxHeapLib
        ConfigDir.hpp
        MinMaxHeap.hpp
        MinMaxHeapTe.inl
        MinMaxHeapMem.inl
        MinMaxHeapCore.inl
)

set_target_properties(MinMaxHeapLib PROPERTIES LINKER_LANGUAGE CXX)
