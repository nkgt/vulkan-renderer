macro(set_compiler_options target)
    target_compile_options(${target} PRIVATE
        /permissive-        # C++ conformance
        /analyze            # Code analysis
        /analyze:external-  # No code analysis for external dependencies
        /utf-8
        /MP
        /GR-
        /Zc:rvalueCast
        /Zc:preprocessor
        /std:c++20
        $<$<CONFIG:Debug>:/Od /Ob0>
        $<$<CONFIG:Release>:/GS- /GF /GT /GL /O2 /Ob2 /Oi /Oy>
    )

    target_link_options(${target}
        PRIVATE $<$<CONFIG:Release>:/LTCG>
        PRIVATE $<$<CONFIG:Debug>:/INCREMENTAL:NO>
    )
endmacro()

# As many warnings as possible
macro(set_warnings target)
    target_compile_options(${target} PRIVATE
        /W4
        /w14242
        /w14254
        /w14263
        /w14265
        /w14287
        /we4289
        /w14296
        /w14311
        /w14545
        /w14546
        /w14547
        /w14549
        /w14555
        /w14619
        /w14640
        /w14826
        /w14905
        /w14906
        /w14928
    )

    target_link_options(${target} PRIVATE /WX)
endmacro()