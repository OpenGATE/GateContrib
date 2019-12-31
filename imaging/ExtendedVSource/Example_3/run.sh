OUTPUT_FILE_NAME=example3_Ps_with_prompt_10M.root
OUTPUT_DIR=output/
DATA_FILE_PATH=${OUTPUT_DIR}${OUTPUT_FILE_NAME}

if [ $# = 0 ]; then

 if [ ! -d ${OUTPUT_DIR} ]; then
  mkdir ${OUTPUT_DIR}
 else
  rm ${OUTPUT_DIR}/*
 fi

 echo "[INFO] Simulation start ..."
 d1=$(date)
 Gate Main.mac
 d2=$(date)
 echo "[INFO] Simulation finished."
 echo "[INFO] START: $d1"
 echo "[INFO] END  : $d2"
fi

if [ $# = 0 ] || [ "$1" == "ONLY_ANALYSIS" ]; then 
 echo "[INFO] Analysis start ..."
 d1=$(date)
 ../program/build/pdp FILE_NAME ${DATA_FILE_PATH} MODEL Ps PROMPT_ENABLE BINS_TIME 100 MIN_TIME 0.0 MAX_TIME 1000.0 BINS_POS 20 MIN_POS -1.0 MAX_POS 1.0
 d2=$(date)
 echo "[INFO] Analysis finished."
 echo "[INFO] START: $d1"
 echo "[INFO] END  : $d2"
 mv *.png output/
fi
echo "***************************"

