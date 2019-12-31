# Positronium Data Plotter ( pdp )

## About

This is program created to visualize data from examples.

## Installation

In console just type:

```bash
bash install.sh
```

## Example of usage

```bash
./psd FILE_NAME data.root MODEL pPs PROMPT_ENABLE BINS_TIME 100 MIN_TIME 0.0 MAX_TIME 1.0 BINS_POS 20 MIN_POS -1.0 MAX_POS 1.0
```

## Commands

General:

* **FILE_NAME** - *.root file name ( from GATE output )

* **MODEL** - for which positronium decay model user wants to present data ( pPs - para-positronium, oPs - ortho-positronium, Ps - mixed decay )

* **PROMPT_ENABLE** - data contains signal from prompt gamma ( source was emitting prompt gammas )

* **PROMPT_DISABLE** - data doesn't contain signal from prompt gamma ( source wasn't emitting prompt gammas )

Positronium lifetime histogram parameterization:

* **BINS_TIME** - bins number ( lifetime histogram )

* **MIN_TIME** - minimal value on x-axis ( lifetime histogram )

* **MAX_TIME** - maximal value on x-axis ( lifetime histogram )

* **LIFETIME** - theoretical positronium lifetime value ( if this value is set, then lifetime plot will contain theoretical curve )

Source position histogram parametrisation:

* **BINS_POS** - bins number ( source position histogram ) 

* **MIN_POS** - minimal value on x-axis and y-axis

* **MAX_POS** - maximal value on x-axis and y-axis



