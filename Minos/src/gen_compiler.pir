
.namespace []
.sub "_block1000"  :anon :subid("10_1369452100.60226")
.annotate 'file', "src/Minos/Compiler.pm"
.annotate 'line', 0
    .const 'Sub' $P1003 = "11_1369452100.60226" 
    capture_lex $P1003
.annotate 'line', 1
    $P0 = find_dynamic_lex "$*CTXSAVE"
    if null $P0 goto ctxsave_done
    $I0 = can $P0, "ctxsave"
    unless $I0 goto ctxsave_done
    $P0."ctxsave"()
  ctxsave_done:
.annotate 'line', 3
    .const 'Sub' $P1003 = "11_1369452100.60226" 
    capture_lex $P1003
    $P101 = $P1003()
.annotate 'line', 1
    .return ($P101)
    .const 'Sub' $P1008 = "13_1369452100.60226" 
    .return ($P1008)
.end


.namespace []
.sub "" :load :init :subid("post14") :outer("10_1369452100.60226")
.annotate 'file', "src/Minos/Compiler.pm"
.annotate 'line', 0
    .const 'Sub' $P1001 = "10_1369452100.60226" 
    .local pmc block
    set block, $P1001
    $P1010 = get_root_global ["parrot"], "P6metaclass"
    $P1010."new_class"("Minos::Compiler", "HLL::Compiler" :named("parent"))
.end


.namespace ["Minos";"Compiler"]
.sub "_block1002"  :subid("11_1369452100.60226") :outer("10_1369452100.60226")
.annotate 'file', "src/Minos/Compiler.pm"
.annotate 'line', 3
    $P0 = find_dynamic_lex "$*CTXSAVE"
    if null $P0 goto ctxsave_done
    $I0 = can $P0, "ctxsave"
    unless $I0 goto ctxsave_done
    $P0."ctxsave"()
  ctxsave_done:
    .return ()
    .const 'Sub' $P1005 = "12_1369452100.60226" 
    .return ($P1005)
.end


.namespace ["Minos";"Compiler"]
.sub "" :load :init :subid("post15") :outer("11_1369452100.60226")
.annotate 'file', "src/Minos/Compiler.pm"
.annotate 'line', 3
    .const 'Sub' $P1003 = "11_1369452100.60226" 
    .local pmc block
    set block, $P1003
.annotate 'line', 4
    get_hll_global $P101, ["Minos"], "Compiler"
    $P101."language"("Minos")
.annotate 'line', 5
    get_hll_global $P101, ["Minos"], "Compiler"
    get_hll_global $P102, ["Minos"], "Grammar"
    $P101."parsegrammar"($P102)
.annotate 'line', 6
    get_hll_global $P101, ["Minos"], "Compiler"
    get_hll_global $P102, ["Minos"], "Actions"
    $P101."parseactions"($P102)
.annotate 'line', 8
    get_hll_global $P101, ["Minos"], "Compiler"
    $P101."commandline_banner"("Minos 0.0000000000001\n")
.annotate 'line', 9
    get_hll_global $P101, ["Minos"], "Compiler"
    $P101."commandline_prompt"("3:(:)")
.end


.namespace ["Minos";"Compiler"]
.sub "_block1004" :load :anon :subid("12_1369452100.60226")
.annotate 'file', "src/Minos/Compiler.pm"
.annotate 'line', 3
    .const '' $P1006 = "11_1369452100.60226" 
    $P100 = $P1006()
    .return ($P100)
.end


.namespace []
.sub "_block1007" :load :anon :subid("13_1369452100.60226")
.annotate 'file', "src/Minos/Compiler.pm"
.annotate 'line', 1
    .const '' $P1009 = "10_1369452100.60226" 
    $P100 = $P1009()
    .return ($P100)
.end

