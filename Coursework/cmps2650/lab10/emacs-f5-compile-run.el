;; --- F5: Save + Compile + Run ----------------------------------------------
(setq compilation-scroll-output t)

(defun my-save-compile-run ()
  "Save buffer, then compile and run based on major-mode.
Supports C, C++, Java, Python, Go (and a generic fallback)."
  (interactive)
  (unless (buffer-file-name) (call-interactively #'write-file))
  (save-buffer)
  (let* ((file  (buffer-file-name))
         (base  (file-name-sans-extension (file-name-nondirectory file)))
         (qfile (shell-quote-argument file))
         (exe   (if (eq system-type 'windows-nt)
                    (concat base ".exe")
                  base))
         (qexe  (shell-quote-argument exe))
         (run   (if (eq system-type 'windows-nt) qexe (concat "./" qexe)))
         (python (or (executable-find "python3")
                     (executable-find "python")
                     "python3"))
         (cmd
          (cond
           ;; C
           ((derived-mode-p 'c-mode)
            (format "gcc -std=c11 -Wall -Wextra -O2 %s -o %s && %s"
                    qfile qexe run))
           ;; C++
           ((derived-mode-p 'c++-mode)
            (format "g++ -std=c++17 -Wall -Wextra -O2 %s -o %s && %s"
                    qfile qexe run))
           ;; Java (main class == filename)
           ((derived-mode-p 'java-mode)
            (format "javac %s && java -cp . %s" qfile base))
           ;; Python
           ((derived-mode-p 'python-mode)
            (format "%s %s" python qfile))
           ;; Go
           ((derived-mode-p 'go-mode)
            (format "go run %s" qfile))
           ;; Fallback: use existing compile-command or ask
           (t (or compile-command
                  (read-shell-command "Compile & run command: "))))))
    (compile cmd)))

(global-set-key (kbd "<f5>") #'my-save-compile-run)
;; ---------------------------------------------------------------------------
