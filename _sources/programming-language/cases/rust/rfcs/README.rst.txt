========================================
Rust RFCs
========================================


.. contents:: 目錄


介紹
========================================

Rust 在做重要的更動時都需要先開 Rust RFC 進行討論，
討論到一定程度後，
如果核心成員覺得沒問題就會接受 RFC。
RFC 需要符合規定的格式，
內容包含動機、設計、如何教其他人、缺點、其他替代方案。

現在 Rust RFC 會用 `rfcbot <https://github.com/anp/rfcbot-rs>`_ 去管理，
大家告訴 rfcbot 同意後，
rfcbot 會負責後續的 PR merge。



Rust RFC 列表
========================================

:URL: https://github.com/rust-lang/rfcs/tree/master/text


* 2420-unreserve-proc.md
    - ``proc`` 這個 keyword 已經沒在用了，未來也不預期會使用，決定拿掉
* 2394-async_await.md
    - Asynchronous I/O 的實做討論，決定現在使用 async/await 的模式，而不是 green-threading (CSP for Go, Actor for Erlang) 或 Monadic transformations (do notation for Haskell)
* 2388-try-expr.md
* 2349-pin.md
    - 新 API 來處理不能被 move 的記憶體
* 2342-const-control-flow.md
* 2341-const-locals.md
* 2338-type-alias-enum-variants.md
* 2333-prior-art.md
    - 未來 Rust RFC 都要有 Prior art 的章節
* 2325-stable-simd.md
* 2318-custom-test-frameworks.md
* 2314-roadmap-2018.md
* 2307-concrete-nonzero-types.md
* 2300-self-in-typedefs.md
* 2298-macro-at-most-once-rep.md
* 2295-os-str-pattern.md
* 2282-profile-dependencies.md
* 2250-finalize-impl-dyn-syntax.md
* 2230-bury-description.md
* 2226-fmt-debug-hex.md
* 2203-const-repeat-expr.md
* 2196-metabuild.md
* 2195-really-tagged-unions.md
* 2175-if-while-or-patterns.md
* 2169-euclidean-modulo.md
* 2166-impl-only-use.md
* 2151-raw-identifiers.md
* 2145-type-privacy.md
* 2141-alternative-registries.md
* 2137-variadic.md
* 2136-build-systems.md
* 2133-all-the-clones.md
* 2132-copy-closures.md
* 2128-use-nested-groups.md
* 2126-path-clarity.md
* 2124-option-filter.md
* 2116-alloc-me-maybe.md
* 2115-argument-lifetimes.md
* 2113-dyn-trait-syntax.md
* 2103-tool-attributes.md
* 2102-unnamed-fields.md
* 2094-nll.md
* 2093-infer-outlives.md
* 2091-inline-semantic.md
* 2089-implied-bounds.md
* 2086-allow-if-let-irrefutables.md
* 2071-impl-trait-type-alias.md
* 2070-panic-implementation.md
* 2057-refcell-replace.md
* 2056-allow-trivial-where-clause-constraints.md
* 2052-epochs.md
* 2046-label-break-value.md
* 2045-target-feature.md
* 2044-license-rfcs.md
* 2043-is-aligned-intrinsic.md
* 2033-experimental-coroutines.md
* 2027-object_safe_for_dispatch.md
* 2025-nested-method-calls.md
* 2011-generic-assert.md
* 2008-non-exhaustive.md
* 2005-match-ergonomics.md
* 2000-const-generics.md
* 1990-external-doc-attribute.md
* 1985-tiered-browser-support.md
* 1983-nursery-deprecation.md
* 1977-public-private-dependencies.md
* 1974-global-allocators.md
* 1969-cargo-prepublish.md
* 1966-unsafe-pointer-reform.md
* 1961-clamp.md
* 1951-expand-impl-trait.md
* 1946-intra-rustdoc-links.md
* 1940-must-use-functions.md
* 1937-ques-in-main.md
* 1925-optional-match-vert.md
* 1909-unsized-rvalues.md
* 1884-unstable-sort.md
* 1869-eprintln.md
* 1868-portability-lint.md
* 1866-more-readable-assert-eq.md
* 1861-extern-types.md
* 1860-manually-drop.md
* 1859-try-trait.md
* 1857-stabilize-drop-order.md
* 1849-non-static-type-id.md
* 1845-shared-from-slice.md
* 1828-rust-bookshelf.md
* 1826-change-doc-default-urls.md
* 1824-crates.io-default-ranking.md
* 1789-as-cell.md
* 1774-roadmap-2017.md
* 1758-repr-transparent.md
* 1733-trait-alias.md
* 1728-north-star.md
* 1725-unaligned-access.md
* 1721-crt-static.md
* 1717-dllimport.md
* 1696-discriminant.md
* 1695-add-error-macro.md
* 1685-deprecate-anonymous-parameters.md
* 1683-docs-team.md
* 1682-field-init-shorthand.md
* 1681-macros-1.1.md
* 1679-panic-safe-slicing.md
* 1665-windows-subsystem.md
* 1660-try-borrow.md
* 1653-assert_ne.md
* 1651-movecell.md
* 1649-atomic-access.md
* 1647-allow-self-in-where-clauses.md
* 1644-default-and-expanded-rustc-errors.md
* 1643-memory-model-strike-team.md
* 1640-duration-checked-sub.md
* 1636-document_all_features.md
* 1624-loop-break-value.md
* 1623-static.md
* 1620-regex-1.0.md
* 1618-ergonomic-format-args.md
* 1607-style-rfcs.md
* 1598-generic_associated_types.md
* 1590-macro-lifetimes.md
* 1589-rustc-bug-fix-procedure.md
* 1584-macros.md
* 1581-fused-iterator.md
* 1576-macros-literal-matcher.md
* 1574-more-api-documentation-conventions.md
* 1567-long-error-codes-explanation-normalization.md
* 1566-proc-macros.md
* 1561-macro-naming.md
* 1560-name-resolution.md
* 1559-attributes-with-literals.md
* 1558-closure-to-fn-coercion.md
* 1552-contains-method-for-various-collections.md
* 1548-global-asm.md
* 1543-integer_atomics.md
* 1542-try-from.md
* 1535-stable-overflow-checks.md
* 1525-cargo-workspace.md
* 1522-conservative-impl-trait.md
* 1521-copy-clone-semantics.md
* 1513-less-unwinding.md
* 1510-cdylib.md
* 1506-adt-kinds.md
* 1504-int128.md
* 1498-ipv6addr-octets.md
* 1492-dotdot-in-patterns.md
* 1479-unix-socket.md
* 1467-volatile.md
* 1461-net2-mutators.md
* 1445-restrict-constants-in-patterns.md
* 1444-union.md
* 1443-extended-compare-and-swap.md
* 1440-drop-types-in-const.md
* 1434-contains-method-for-ranges.md
* 1432-replace-slice.md
* 1422-pub-restricted.md
* 1419-slice-copy.md
* 1415-trim-std-os.md
* 1414-rvalue_static_promotion.md
* 1399-repr-pack.md
* 1398-kinds-of-allocators.md
* 1361-cargo-cfg-dependencies.md
* 1359-process-ext-unix.md
* 1358-repr-align.md
* 1331-grammar-is-canonical.md
* 1328-global-panic-handler.md
* 1327-dropck-param-eyepatch.md
* 1317-ide.md
* 1307-osstring-methods.md
* 1300-intrinsic-semantics.md
* 1298-incremental-compilation.md
* 1291-promote-libc.md
* 1288-time-improvements.md
* 1270-deprecation.md
* 1268-allow-overlapping-impls-on-marker-traits.md
* 1260-main-reexport.md
* 1257-drain-range-2.md
* 1252-open-options.md
* 1242-rust-lang-crates.md
* 1241-no-wildcard-deps.md
* 1240-repr-packed-unsafe-ref.md
* 1238-nonparametric-dropck.md
* 1236-stabilize-catch-panic.md
* 1229-compile-time-asserts.md
* 1228-placement-left-arrow.md
* 1219-use-group-as.md
* 1216-bang-type.md
* 1214-projections-lifetimes-and-wf.md
* 1212-line-endings.md
* 1211-mir.md
* 1210-impl-specialization.md
* 1201-naked-fns.md
* 1200-cargo-install.md
* 1199-simd-infrastructure.md
* 1194-set-recovery.md
* 1193-cap-lints.md
* 1192-inclusive-ranges.md
* 1191-hir.md
* 1184-stabilize-no_std.md
* 1183-swap-out-jemalloc.md
* 1174-into-raw-fd-socket-handle-traits.md
* 1156-adjust-default-object-bounds.md
* 1152-slice-string-symmetry.md
* 1135-raw-pointer-comparisons.md
* 1131-likely-intrinsic.md
* 1123-str-split-at.md
* 1122-language-semver.md
* 1119-result-expect.md
* 1105-api-evolution.md
* 1102-rename-connect-to-join.md
* 1096-remove-static-assert.md
* 1068-rust-governance.md
* 1066-safe-mem-forget.md
* 1058-slice-tail-redesign.md
* 1057-io-error-sync.md
* 1054-str-words.md
* 1048-rename-soft-link-to-symlink.md
* 1047-socket-timeouts.md
* 1044-io-fs-2.1.md
* 1040-duration-reform.md
* 1030-prelude-additions.md
* 1023-rebalancing-coherence.md
* 1014-stdout-existential-crisis.md
* 1011-process.exit.md
* 0982-dst-coercion.md
* 0980-read-exact.md
* 0979-align-splitn-with-other-languages.md
* 0968-closure-return-type-syntax.md
* 0953-op-assign.md
* 0940-hyphens-considered-harmful.md
* 0921-entry_v3.md
* 0911-const-fn.md
* 0909-move-thread-local-to-std-thread.md
* 0888-compiler-fence-intrinsics.md
* 0879-small-base-lexing.md
* 0873-type-macros.md
* 0840-no-panic-in-c-string.md
* 0839-embrace-extend-extinguish.md
* 0832-from-elem-with-love.md
* 0823-hash-simplification.md
* 0809-box-and-in-for-stdlib.md
* 0803-type-ascription.md
* 0771-std-iter-once.md
* 0769-sound-generic-drop.md
* 0738-variance.md
* 0736-privacy-respecting-fru.md
* 0735-allow-inherent-impls-anywhere.md
* 0702-rangefull-expression.md
* 0640-debug-improvements.md
* 0639-discriminant-intrinsic.md
* 0601-replace-be-with-become.md
* 0599-default-object-bound.md
* 0593-forbid-Self-definitions.md
* 0592-c-str-deref.md
* 0587-fn-return-should-be-an-associated-type.md
* 0580-rename-collections.md
* 0574-drain-range.md
* 0572-rustc-attribute.md
* 0565-show-string-guidelines.md
* 0563-remove-ndebug.md
* 0560-integer-overflow.md
* 0558-require-parentheses-for-chained-comparisons.md
* 0556-raw-lifetime.md
* 0550-macro-future-proofing.md
* 0546-Self-not-sized-by-default.md
* 0544-rename-int-uint.md
* 0534-deriving2derive.md
* 0533-no-array-elem-moves.md
* 0532-self-in-use.md
* 0531-define-rfc-scope.md
* 0529-conversion-traits.md
* 0528-string-patterns.md
* 0526-fmt-text-writer.md
* 0522-self-impl.md
* 0520-new-array-repeat-syntax.md
* 0517-io-os-reform.md
* 0509-collections-reform-part-2.md
* 0507-release-channels.md
* 0505-api-comment-conventions.md
* 0504-show-stabilization.md
* 0503-prelude-stabilization.md
* 0501-consistent_no_prelude_attributes.md
* 0495-array-pattern-changes.md
* 0494-c_str-and-c_vec-stability.md
* 0490-dst-syntax.md
* 0486-std-ascii-reform.md
* 0474-path-reform.md
* 0469-feature-gate-box-patterns.md
* 0463-future-proof-literal-suffixes.md
* 0461-tls-overhaul.md
* 0459-disallow-shadowing.md
* 0458-send-improvements.md
* 0453-macro-reform.md
* 0450-un-feature-gate-some-more-gates.md
* 0447-no-unused-impl-parameters.md
* 0446-es6-unicode-escapes.md
* 0445-extension-trait-conventions.md
* 0439-cmp-ops-reform.md
* 0438-precedence-of-plus.md
* 0430-finalizing-naming-conventions.md
* 0418-struct-variants.md
* 0404-change-prefer-dynamic.md
* 0403-cargo-build-command.md
* 0401-coercions.md
* 0390-enum-namespacing.md
* 0387-higher-ranked-trait-bounds.md
* 0385-module-system-cleanup.md
* 0380-stabilize-std-fmt.md
* 0379-remove-reflection.md
* 0378-expr-macros.md
* 0369-num-reform.md
* 0356-no-module-prefixes.md
* 0344-conventions-galore.md
* 0342-keywords.md
* 0341-remove-virtual-structs.md
* 0339-statically-sized-literals.md
* 0326-restrict-xXX-to-ascii.md
* 0320-nonzeroing-dynamic-drop.md
* 0256-remove-refcounting-gc-of-t.md
* 0255-object-safety.md
* 0246-const-vs-static.md
* 0243-trait-based-exception-handling.md
* 0241-deref-conversions.md
* 0240-unsafe-api-location.md
* 0236-error-conventions.md
* 0235-collections-conventions.md
* 0234-variants-namespace.md
* 0231-upvar-capture-inference.md
* 0230-remove-runtime.md
* 0221-panic.md
* 0218-empty-struct-with-braces.md
* 0216-collection-views.md
* 0214-while-let.md
* 0213-defaulted-type-params.md
* 0212-restore-int-fallback.md
* 0202-subslice-syntax-change.md
* 0201-error-chaining.md
* 0199-ownership-variants.md
* 0198-slice-notation.md
* 0195-associated-items.md
* 0194-cfg-syntax.md
* 0192-bounds-on-object-and-generic-types.md
* 0184-tuple-accessors.md
* 0179-and-mut-patterns.md
* 0169-use-path-as-id.md
* 0168-mod.md
* 0164-feature-gate-slice-pats.md
* 0160-if-let.md
* 0155-anonymous-impl-only-in-same-module.md
* 0151-capture-by-value.md
* 0141-lifetime-elision.md
* 0139-remove-cross-borrowing-entirely.md
* 0136-no-privates-in-public.md
* 0135-where.md
* 0132-ufcs.md
* 0131-target-specification.md
* 0130-box-not-special.md
* 0123-share-to-threadsafe.md
* 0116-no-module-shadowing.md
* 0115-rm-integer-fallback.md
* 0114-closures.md
* 0112-remove-cross-borrowing.md
* 0111-index-traits.md
* 0109-remove-crate-id.md
* 0107-pattern-guards-with-bind-by-move.md
* 0100-partial-cmp.md
* 0093-remove-format-intl.md
* 0092-struct-grammar.md
* 0090-lexical-syntax-simplification.md
* 0089-loadable-lints.md
* 0087-trait-bounds-with-plus.md
* 0086-plugin-registrar.md
* 0085-pattern-macros.md
* 0079-undefined-struct-layout.md
* 0071-const-block-expr.md
* 0069-ascii-literals.md
* 0068-const-unsafe-pointers.md
* 0066-better-temporary-lifetimes.md
* 0063-module-file-system-hierarchy.md
* 0060-rename-strbuf.md
* 0059-remove-tilde.md
* 0050-assert.md
* 0049-match-arm-attributes.md
* 0048-traits.md
* 0042-regexps.md
* 0040-libstd-facade.md
* 0034-bounded-type-parameters.md
* 0026-remove-priv.md
* 0019-opt-in-builtin-traits.md
* 0016-more-attributes.md
* 0008-new-intrinsics.md
* 0003-attribute-usage.md
* 0002-rfc-process.md
* 0001-private-fields.md



別人提 RFC 的經驗
========================================

* `From Tweet to Rust Feature <https://llogiq.github.io/2016/09/14/feature.html>`_



RFC 1444 - union
========================================

:RFC: https://github.com/rust-lang/rfcs/blob/master/text/1444-union.md
:PR: https://github.com/rust-lang/rfcs/pulls/1444
:Tracking: https://github.com/rust-lang/rust/issues/32836



RFC 1504 - int128
========================================

:RFC: https://github.com/rust-lang/rfcs/blob/master/text/1504-int128.md
:PR: https://github.com/rust-lang/rfcs/pull/1504
:Tracking: https://github.com/rust-lang/rust/issues/35118


這個 RFC 的目標是加入 ``i128`` 和 ``u128`` 這兩個 primitive type，
藉此用比較有效率的實做取代部份需要使用 BigNum 的地方，
也避免掉使用 BigNum 時的 Heap allocation 和較高 overhead 的操作，
而 128 位元數字將由 LLVM 提供有效率的實做（在 C 中已經可以經由 Clang 來使用 ``__int128`` ）。



RFC 2025 - Enable Nested Method Calls
========================================

:RFC: https://github.com/rust-lang/rfcs/blob/master/text/2025-nested-method-calls.md
:PR: https://github.com/rust-lang/rfcs/pull/2025
:Tracking: https://github.com/rust-lang/rust/issues/44100


這 RFC 的目標是要允許巢狀的 borrow，
例如 ``vec.push(vec.len())`` ，
vec 先是 mutable borrow，
然後裡面又有 shared borrow，
原本這樣的程式碼是不能編譯的，
但是經過這 RFC 以後，
只要裡面的借用是唯讀且生命週期只在其中，
那裡面的借用就被允許。

實做上會把 MIR 的 mutable borrow 改成兩階段借用，
第一階段只保留會被更動的狀態，
此時還可以進行生命週期內的唯讀借用，
等到真的要進行更動的操作時才會變成完全地更動借用。



Misc
========================================

* `Rust RFCs - 0198 - Slice Notation <https://github.com/rust-lang/rfcs/blob/master/text/0198-slice-notation.md>`_
    - foo.as_slice()    => ``foo[]``
    - foo.slice(n, m)   => ``foo[n..m]``
    - foo.slice_from(n) => ``foo[n..]``
    - foo.slice_to(m)   => ``foo[..m]``
    - `PR <https://github.com/rust-lang/rfcs/pull/198>`_

* `Rust RFCs - 0199 - Ownership Variants <https://github.com/rust-lang/rfcs/blob/master/text/0199-ownership-variants.md>`_
    - ``_mut`` suffix
    - `PR <https://github.com/rust-lang/rfcs/pull/199>`_

* `Rust RFCs - 0520 - New Array Repeat Syntax <https://github.com/rust-lang/rfcs/blob/master/text/0520-new-array-repeat-syntax.md>`_
    - ``[T, ..N]`` => ``[T; N]``
    - `PR <https://github.com/rust-lang/rfcs/pull/520>`_

* `Rust RFCs - 0544 - Rename "int" & "uint" <https://github.com/rust-lang/rfcs/blob/master/text/0544-rename-int-uint.md>`_

    - ``int`` & ``uint`` => ``isize`` & ``usize``
    - `PR <https://github.com/rust-lang/rfcs/pull/544>`_
