;; Add:
;;
;;    (add-to-list 'load-path (concat (getenv "OCCA_DIR") "/editorTools"))
;;    (require 'okl-mode)
;;
;; to your ~/.emacs file to use [okl-mode] for .okl files

;;---[ OKL Mode ]-------------

(define-derived-mode okl-mode c++-mode
  "OKL"
  "[O]CCA [K]ernel [L]anguage mode."
)

(defun add-okl-keywords()
  "Adds OKL keywords"
  ;
  (font-lock-add-keywords nil
    '(("\\<\\(kernel\\)"         . 'font-lock-keyword-face)
      ("\\<\\(device\\)"         . 'font-lock-keyword-face)
      ("\\<\\(occaFunction\\)"   . 'font-lock-keyword-face)
      ("\\<\\(shared\\)"         . 'font-lock-keyword-face)
      ("\\<\\(exclusive\\)"      . 'font-lock-keyword-face)
      ("\\<\\(outer0\\)"         . 'font-lock-keyword-face)
      ("\\<\\(outer1\\)"         . 'font-lock-keyword-face)
      ("\\<\\(outer2\\)"         . 'font-lock-keyword-face)
      ("\\<\\(inner0\\)"         . 'font-lock-keyword-face)
      ("\\<\\(inner1\\)"         . 'font-lock-keyword-face)
      ("\\<\\(inner2)\\)"        . 'font-lock-keyword-face)

      ("\\<\\(barrier\\)"        . 'font-lock-builtin-face)
      ("\\<\\(localMemFence\\)"  . 'font-lock-constant-face)
      ("\\<\\(globalMemFence\\)" . 'font-lock-constant-face)
      )
    )
)

(add-hook 'okl-mode-hook 'add-okl-keywords)

(add-to-list 'auto-mode-alist '("\\.okl\\'" . okl-mode))
(add-to-list 'auto-mode-alist '("\\.ofl\\'" . f90-mode))

;;---[ OCCA Mode ]------------

(define-derived-mode occa-mode c++-mode
  "OCCA"
  "OCCA Mode."
)

(defun add-occa-keywords()
  "Adds OCCA keywords"
  ;
  (font-lock-add-keywords nil
    '(("\\<\\(occaOuterDim2\\)"    . 'font-lock-constant-face)
      ("\\<\\(occaOuterId2\\)"     . 'font-lock-constant-face)
      ("\\<\\(occaOuterDim1\\)"    . 'font-lock-constant-face)
      ("\\<\\(occaOuterId1\\)"     . 'font-lock-constant-face)
      ("\\<\\(occaOuterDim0\\)"    . 'font-lock-constant-face)
      ("\\<\\(occaOuterId0\\)"     . 'font-lock-constant-face)
      ("\\<\\(occaInnerDim2\\)"    . 'font-lock-constant-face)
      ("\\<\\(occaInnerId2\\)"     . 'font-lock-constant-face)
      ("\\<\\(occaInnerDim1\\)"    . 'font-lock-constant-face)
      ("\\<\\(occaInnerId1\\)"     . 'font-lock-constant-face)
      ("\\<\\(occaInnerDim0\\)"    . 'font-lock-constant-face)
      ("\\<\\(occaInnerId0\\)"     . 'font-lock-constant-face)
      ("\\<\\(occaGlobalDim2\\)"   . 'font-lock-constant-face)
      ("\\<\\(occaGlobalId2\\)"    . 'font-lock-constant-face)
      ("\\<\\(occaGlobalDim1\\)"   . 'font-lock-constant-face)
      ("\\<\\(occaGlobalId1\\)"    . 'font-lock-constant-face)
      ("\\<\\(occaGlobalDim0\\)"   . 'font-lock-constant-face)
      ("\\<\\(occaGlobalId0\\)"    . 'font-lock-constant-face)
      ("\\<\\(occaOuterFor2\\)"    . 'font-lock-constant-face)
      ("\\<\\(occaOuterFor1\\)"    . 'font-lock-constant-face)
      ("\\<\\(occaOuterFor0\\)"    . 'font-lock-constant-face)
      ("\\<\\(occaOuterFor\\)"     . 'font-lock-constant-face)
      ("\\<\\(occaInnerFor2\\)"    . 'font-lock-constant-face)
      ("\\<\\(occaInnerFor1\\)"    . 'font-lock-constant-face)
      ("\\<\\(occaInnerFor0\\)"    . 'font-lock-constant-face)
      ("\\<\\(occaInnerFor\\)"     . 'font-lock-constant-face)
      ("\\<\\(occaGlobalFor0\\)"   . 'font-lock-constant-face)
      ("\\<\\(occaParallelFor2\\)" . 'font-lock-constant-face)
      ("\\<\\(occaParallelFor1\\)" . 'font-lock-constant-face)
      ("\\<\\(occaParallelFor0\\)" . 'font-lock-constant-face)
      ("\\<\\(occaParallelFor\\)"  . 'font-lock-constant-face)

      ("\\<\\(occaLocalMemFence\\)"  . 'font-lock-constant-face)
      ("\\<\\(occaGlobalMemFence\\)" . 'font-lock-constant-face)
      ("\\<\\(occaContinue\\)"       . 'font-lock-constant-face)

      ("\\<\\(occaKernelInfoArg\\)"   . 'font-lock-constant-face)
      ("\\<\\(occaFunctionInfoArg\\)" . 'font-lock-constant-face)
      ("\\<\\(occaFunctionInfo\\)"    . 'font-lock-constant-face)

      ("\\<\\(occaShared\\)"         . 'font-lock-keyword-face)
      ("\\<\\(occaPointer\\)"        . 'font-lock-keyword-face)
      ("\\<\\(occaVariable\\)"       . 'font-lock-keyword-face)
      ("\\<\\(occaRestrict\\)"       . 'font-lock-keyword-face)
      ("\\<\\(occaVolatile\\)"       . 'font-lock-keyword-face)
      ("\\<\\(occaAligned\\)"        . 'font-lock-keyword-face)
      ("\\<\\(occaFunctionShared\\)" . 'font-lock-keyword-face)
      ("\\<\\(occaConst\\)"          . 'font-lock-keyword-face)
      ("\\<\\(occaConstant\\)"       . 'font-lock-keyword-face)
      ("\\<\\(occaKernel\\)"         . 'font-lock-keyword-face)
      ("\\<\\(occaFunction\\)"       . 'font-lock-keyword-face)
      ("\\<\\(occaDeviceFunction\\)" . 'font-lock-keyword-face)
      ("\\<\\(occaReadOnly\\)"       . 'font-lock-keyword-face)
      ("\\<\\(occaWriteOnly\\)"      . 'font-lock-keyword-face)

      ("\\<\\(occaTexture1D\\)" . 'font-lock-keyword-face)
      ("\\<\\(occaTexture2D\\)" . 'font-lock-keyword-face)

      ("\\<\\(occaFabs\\)"        . 'font-lock-builtin-face)
      ("\\<\\(occaFastFabs\\)"    . 'font-lock-builtin-face)
      ("\\<\\(occaNativeFabs\\)"  . 'font-lock-builtin-face)
      ("\\<\\(occaSqrt\\)"        . 'font-lock-builtin-face)
      ("\\<\\(occaFastSqrt\\)"    . 'font-lock-builtin-face)
      ("\\<\\(occaNativeSqrt\\)"  . 'font-lock-builtin-face)
      ("\\<\\(occaCbrt\\)"        . 'font-lock-builtin-face)
      ("\\<\\(occaFastCbrt\\)"    . 'font-lock-builtin-face)
      ("\\<\\(occaNativeCbrt\\)"  . 'font-lock-builtin-face)
      ("\\<\\(occaSin\\)"         . 'font-lock-builtin-face)
      ("\\<\\(occaFastSin\\)"     . 'font-lock-builtin-face)
      ("\\<\\(occaNativeSin\\)"   . 'font-lock-builtin-face)
      ("\\<\\(occaAsin\\)"        . 'font-lock-builtin-face)
      ("\\<\\(occaFastAsin\\)"    . 'font-lock-builtin-face)
      ("\\<\\(occaNativeAsin\\)"  . 'font-lock-builtin-face)
      ("\\<\\(occaSinh\\)"        . 'font-lock-builtin-face)
      ("\\<\\(occaFastSinh\\)"    . 'font-lock-builtin-face)
      ("\\<\\(occaNativeSinh\\)"  . 'font-lock-builtin-face)
      ("\\<\\(occaAsinh\\)"       . 'font-lock-builtin-face)
      ("\\<\\(occaFastAsinh\\)"   . 'font-lock-builtin-face)
      ("\\<\\(occaNativeAsinh\\)" . 'font-lock-builtin-face)
      ("\\<\\(occaCos\\)"         . 'font-lock-builtin-face)
      ("\\<\\(occaFastCos\\)"     . 'font-lock-builtin-face)
      ("\\<\\(occaNativeCos\\)"   . 'font-lock-builtin-face)
      ("\\<\\(occaAcos\\)"        . 'font-lock-builtin-face)
      ("\\<\\(occaFastAcos\\)"    . 'font-lock-builtin-face)
      ("\\<\\(occaNativeAcos\\)"  . 'font-lock-builtin-face)
      ("\\<\\(occaCosh\\)"        . 'font-lock-builtin-face)
      ("\\<\\(occaFastCosh\\)"    . 'font-lock-builtin-face)
      ("\\<\\(occaNativeCosh\\)"  . 'font-lock-builtin-face)
      ("\\<\\(occaAcosh\\)"       . 'font-lock-builtin-face)
      ("\\<\\(occaFastAcosh\\)"   . 'font-lock-builtin-face)
      ("\\<\\(occaNativeAcosh\\)" . 'font-lock-builtin-face)
      ("\\<\\(occaTan\\)"         . 'font-lock-builtin-face)
      ("\\<\\(occaFastTan\\)"     . 'font-lock-builtin-face)
      ("\\<\\(occaNativeTan\\)"   . 'font-lock-builtin-face)
      ("\\<\\(occaAtan\\)"        . 'font-lock-builtin-face)
      ("\\<\\(occaFastAtan\\)"    . 'font-lock-builtin-face)
      ("\\<\\(occaNativeAtan\\)"  . 'font-lock-builtin-face)
      ("\\<\\(occaTanh\\)"        . 'font-lock-builtin-face)
      ("\\<\\(occaFastTanh\\)"    . 'font-lock-builtin-face)
      ("\\<\\(occaNativeTanh\\)"  . 'font-lock-builtin-face)
      ("\\<\\(occaAtanh\\)"       . 'font-lock-builtin-face)
      ("\\<\\(occaFastAtanh\\)"   . 'font-lock-builtin-face)
      ("\\<\\(occaNativeAtanh\\)" . 'font-lock-builtin-face)
      ("\\<\\(occaExp\\)"         . 'font-lock-builtin-face)
      ("\\<\\(occaFastExp\\)"     . 'font-lock-builtin-face)
      ("\\<\\(occaNativeExp\\)"   . 'font-lock-builtin-face)
      ("\\<\\(occaExpm1\\)"       . 'font-lock-builtin-face)
      ("\\<\\(occaFastExpm1\\)"   . 'font-lock-builtin-face)
      ("\\<\\(occaNativeExpm1\\)" . 'font-lock-builtin-face)
      ("\\<\\(occaPow\\)"         . 'font-lock-builtin-face)
      ("\\<\\(occaFastPow\\)"     . 'font-lock-builtin-face)
      ("\\<\\(occaNativePow\\)"   . 'font-lock-builtin-face)
      ("\\<\\(occaLog2\\)"        . 'font-lock-builtin-face)
      ("\\<\\(occaFastLog2\\)"    . 'font-lock-builtin-face)
      ("\\<\\(occaNativeLog2\\)"  . 'font-lock-builtin-face)
      ("\\<\\(occaLog10\\)"       . 'font-lock-builtin-face)
      ("\\<\\(occaFastLog10\\)"   . 'font-lock-builtin-face)
      ("\\<\\(occaNativeLog10\\)" . 'font-lock-builtin-face)

      ("\\<\\(occaBarrier\\)"      . 'font-lock-builtin-face)
      ("\\<\\(occaInnerBarrier\\)" . 'font-lock-builtin-face)
      ("\\<\\(occaOuterBarrier\\)" . 'font-lock-builtin-face)
      ("\\<\\(occaUnroll\\)"       . 'font-lock-builtin-face)
      ("\\<\\(occaPrivateArray\\)" . 'font-lock-builtin-face)
      ("\\<\\(occaPrivate\\)"      . 'font-lock-builtin-face)
      )
    )
)


(add-hook 'occa-mode-hook 'add-occa-keywords)

(add-to-list 'auto-mode-alist '("\\.occa\\'" . occa-mode))

(provide 'okl-mode)
(provide 'occa-mode)