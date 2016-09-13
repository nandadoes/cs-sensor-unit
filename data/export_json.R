# http://www.r-tutor.com/r-introduction/data-frame/data-import
# dfrm <- read.table("someTxtFiles/03072819.TXT", sep=",", col.names=c("id", "ligh", "airTemp", "airHum", "soilTemp", "soilHum", "airPress", "remainV"))
# dfrm <- read.table("someTxtFiles/03072819.TXT")
# print(dfrm)

# dfrm1 <- read.table("someTxtFiles/03072820.TXT", sep=",", col.names=c("id", "light", "airTemp", "airHum", "soilTemp", "soilHum", "airPress", "remainV"))
# print(dfrm1)


# How to 
# 1) merge all .txt files in a folder into a .cvs file via terminal u
# using the following command:
#         cat *.TXT >merged.csv
# REF: merge multiple file with mac os x terminal http://monchito.com/blog/merge-csv-files-with-mac-os-x-terminal

# 2) import the merged file into a dataframe using read.table with colnames parameters
d <- read.table("SEEDS01_CVS/_merged.csv", sep=",", col.names=c("id", "light", "airTemp", "airHum", "soilTemp", "soilHum", "airPress", "remainV"))
# d <- read.table("someTxtFiles_2/merged.csv", sep=",", col.names=c("id", "light", "airTemp", "airHum", "soilTemp", "soilHum", "airPress", "remainV"))
# print(d)

# 3) export to JSON using package: jsonlite
# https://cran.r-project.org/web/packages/jsonlite/vignettes/json-aaquickstart.html 
# https://www.r-bloggers.com/new-package-jsonlite-a-smarter-json-encoderdecoder/

# install 
install.packages("jsonlite", repos="http://cran.r-project.org")

# load 
library(jsonlite)

# Convert dataframe object into json object 
json_data <- toJSON(d, pretty=TRUE)
# Print output to the screen using cat() function see: http://rfunction.com/archives/1866
# cat(json_data)
## Export to JSON format using jsonlite library
write(json_data, "Export_files/seeds01.json")

## Revert json object to dataframe object
# df_data <- fromJSON(json_data)
# # Export the dataframe object into a text file
# write.table(d, "Export_files/testWriteD.txt", sep="\t")

## ...into Excel spreadsheet 
# install.packages("xlsx", repos="http://cran.r-project.org")
# library(xlsx)
# write.xlsx(d, "Export_files/testWriteD.xlsx")


