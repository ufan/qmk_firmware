switch (combo_index) {
 case CAPS_WORD:
     if (pressed) {
#ifdef AUTO_SHIFT_ENABLE
         autoshift_disable();
#endif

         caps_word_set(true);
     }
     break;
 }
