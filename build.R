
## build
file.copy("doc/shinyapp.html", "inst/shiny/interface/www/shinyapp.html", overwrite = TRUE)
devtools::build()

pkgdown::build_site(install = FALSE)
## fix path to images
lines <- readLines("docs/articles/shinyapp.html")
lines <- gsub("../../../../Box%20Sync/R%20projects/causaloptim/vignettes/", "", lines)
writeLines(lines, con = "docs/articles/shinyapp.html")
