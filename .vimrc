let &path .="inc"
nnoremap <F4> :make!<cr>
nnoremap <F5> :!./tetriminos<cr>
augroup project
    autocmd!
    autocmd BufRead,BufNewFile *.h,*.c set filetype=c.doxygen
augroup END

