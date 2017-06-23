#!/bin/sh
POSIXLY_CORRECT=yes
DIR=$(pwd)
NORM=0
N_CHECK=0
I_CHECK=0


# chovani podle zadanych parametru
while getopts "ni:" opt
do
	 case $opt in
	 	i) IGNOR=$OPTARG; I_CHECK=$((I_CHECK +1))
	 	   if [ "$IGNOR" == "-n" ]
	 	   then
	 	     echo "ERROR: Missing additional -i parameter!" 1>&2
	 	     exit 2
	 	   fi ;;
	 	n) NORM=1; N_CHECK=$((N_CHECK +1)) ;;
	 	\?) echo "ERROR: Unknown parameter!" 1>&2 ; exit 1 ;;
	  esac;
done
shift $(($OPTIND - 1))
if [ "$N_CHECK" -gt 1 ] || [ "$I_CHECK" -gt 1 ]
   then echo "ERROR: Too many -n or -i parameters!" 1>&2 ; exit 5
fi
if [ "$1" != "" ]
   then DIR=$1
   if [ ! -d "$DIR" ] 
    then echo "ERROR: Directory doesn't exist!" 1>&2 ; exit 4
   fi
fi
if [ "$2" != "" ]
   then echo "ERROR: Too many parameters!" 1>&2 ; exit 3
fi
#nastaveni normalizace pro FILE_SIZE_HISTOGRAM
if [ "$NORM" -eq 1 ]
 then
  if [ -t 1 ]
   then L_SIZE=$(tput cols); L_SIZE=$((L_SIZE-12))
   else L_SIZE=68 #(79-11)
  fi
fi
#POINTERS
ND=$(find $DIR -type d ! -name "$IGNOR" |wc -l)
NF=$(find $DIR -type f ! -name "$IGNOR" |wc -l) 
echo "Root directory: $DIR"
echo "Directories: $ND"
echo "All files: $NF"
#
#FILE SIZE HISTOGRAM
#
echo "File size histogram:"
COUNT=$(find $DIR -type f ! -name "$IGNOR" -size -100c|wc -l)
if [ "$NORM" -eq 1 ] && [ "$COUNT" -gt "$L_SIZE" ]
 then COUNT=$L_SIZE
fi
printf "  <100 B  : "; if [ "$COUNT" -ne 0 ]; then printf "%0.s#" $(seq  $COUNT);fi ; printf "\n"

COUNT=$(find $DIR -type f ! -name "$IGNOR" -size -1024c -a -size +99c|wc -l)
if [ "$NORM" -eq 1 ] && [ "$COUNT" -gt "$L_SIZE" ]
 then COUNT=$L_SIZE
fi
printf "  <1 KiB  : "; if [ "$COUNT" -ne 0 ]; then printf "%0.s#" $(seq  $COUNT);fi ; printf "\n"

COUNT=$(find $DIR -type f ! -name "$IGNOR" -size -10240c -a -size +1023c|wc -l)
if [ "$NORM" -eq 1 ] && [ "$COUNT" -gt "$L_SIZE" ]
 then COUNT=$L_SIZE
fi
printf "  <10 KiB : "; if [ "$COUNT" -ne 0 ]; then printf "%0.s#" $(seq  $COUNT);fi ; printf "\n"

COUNT=$(find $DIR -type f ! -name "$IGNOR" -size -102400c -a -size +10239c|wc -l)
if [ "$NORM" -eq 1 ] && [ "$COUNT" -gt "$L_SIZE" ]
 then COUNT=$L_SIZE
fi
printf "  <100 KiB: "; if [ "$COUNT" -ne 0 ]; then printf "%0.s#" $(seq  $COUNT);fi ; printf "\n"

COUNT=$(find $DIR -type f ! -name "$IGNOR" -size -1048576c -a -size +102399c|wc -l)
if [ "$NORM" -eq 1 ] && [ "$COUNT" -gt "$L_SIZE" ]
 then COUNT=$L_SIZE
fi
printf "  <1 MiB  : "; if [ "$COUNT" -ne 0 ]; then printf "%0.s#" $(seq  $COUNT);fi ; printf "\n"

COUNT=$(find $DIR -type f ! -name "$IGNOR" -size -10485760c -a -size +1023999c|wc -l)
if [ "$NORM" -eq 1 ] && [ "$COUNT" -gt "$L_SIZE" ]
 then COUNT=$L_SIZE
fi
printf "  <10 MiB : "; if [ "$COUNT" -ne 0 ]; then printf "%0.s#" $(seq  $COUNT);fi ; printf "\n"

COUNT=$(find $DIR -type f ! -name "$IGNOR" -size -104857600c -a -size +10239999c|wc -l)
if [ "$NORM" -eq 1 ] && [ "$COUNT" -gt "$L_SIZE" ]
 then COUNT=$L_SIZE
fi
printf "  <100 MiB: "; if [ "$COUNT" -ne 0 ]; then printf "%0.s#" $(seq  $COUNT);fi ; printf "\n"

COUNT=$(find $DIR -type f ! -name "$IGNOR" -size -1073741824c -a -size +10239999c|wc -l)
if [ "$NORM" -eq 1 ] && [ "$COUNT" -gt "$L_SIZE" ]
 then COUNT=$L_SIZE
fi
printf "  <1 GiB  : "; if [ "$COUNT" -ne 0 ]; then printf "%0.s#" $(seq  $COUNT);fi ; printf "\n"

COUNT=$(find $DIR -type f ! -name "$IGNOR" -size +1073741823c|wc -l)
if [ "$NORM" -eq 1 ] && [ "$COUNT" -gt "$L_SIZE" ]
 then COUNT=$L_SIZE
fi
printf "  >=1 GiB : "; if [ "$COUNT" -ne 0 ]; then printf "%0.s#" $(seq  $COUNT);fi ; printf "\n"
#
#FILE TYPE HISTOGRAM
#
echo "File type histogram:"
#vystup programu FILE serazeny podle cetnosti na 10 nejcastejsich
ALL_TYPES=$(find $DIR -type f ! -name "$IGNOR" -print0 | xargs -0 file -b|cut -c-40| sort| uniq -c| sort -nr| head -n10)
NUMBER_OF_TYPES=$(echo "$ALL_TYPES" |wc -l)

#nastaveni normalizace pro FILE_SIZE_HISTOGRAM
if [ "$NORM" -eq 1 ]
 then
  if [ -t 1 ]
   then L_SIZE=$(tput cols); L_SIZE=$((L_SIZE-47))
   else L_SIZE=33 #(79-46)
  fi
fi

#Vypis jednotlivych kategorii
for i in `seq 1 $NUMBER_OF_TYPES`;
        do
                
                TYPE=$(echo "$ALL_TYPES"|sed ''$i'q;d'| cut -c9-)
                strlen=$(echo "$TYPE" | wc -c)
				COUNT=$(echo "$ALL_TYPES"|sed ''$i'q;d'| awk '{print $1}')
				if [ "$NORM" -eq 1 ] && [ "$COUNT" -gt "$L_SIZE" ]
                 then COUNT=$L_SIZE
                fi
                #retezec kratsi nez 40 znaku
				if [ "$strlen" -lt 40 ]
				 then SPACES=$((44 - strlen))
				      printf "  $TYPE"; printf "%0.s " $(seq  $SPACES); printf ": "
				fi
				#retezec delsi nez 40
				if [ "$strlen" -gt 39 ]
				 then  printf "  $TYPE"; printf "...: "
			    fi
				printf "%0.s#" $(seq  $COUNT); printf "\n"
        done

