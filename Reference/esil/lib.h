fprintf(output, "FUNCinitialize:\n");
fprintf(output, "PUSH BP\n");
fprintf(output, "MOV BP, SP\n");
fprintf(output, "MOV R0, BP\n");
fprintf(output, "MOV R1, 1\n");
fprintf(output, "ADD R0, R1\n");
fprintf(output, "MOV SP, R0\n");
fprintf(output, "MOV [256], 0\n");
fprintf(output, "MOV R0, 0\n");
fprintf(output, "MOV R1, BP\n");
fprintf(output, "MOV R2, 1\n");
fprintf(output, "ADD R2, R1\n");
fprintf(output, "MOV [R2], R0\n");
fprintf(output, "WHILES1:\n");
fprintf(output, "MOV R0, BP\n");
fprintf(output, "MOV R1, 1\n");
fprintf(output, "ADD R1, R0\n");
fprintf(output, "MOV R0, [R1]\n");
fprintf(output, "MOV R1, 256\n");
fprintf(output, "LT R0 R1\n");
fprintf(output, "JZ R0, ENDWHILE1\n");
fprintf(output, "MOV R0, 0\n");
fprintf(output, "MOV R1, BP\n");
fprintf(output, "MOV R2, 1\n");
fprintf(output, "ADD R2, R1\n");
fprintf(output, "MOV R1, [R2]\n");
fprintf(output, "MOV R2, 0\n");
fprintf(output, "ADD R1, R2\n");
fprintf(output, "MOV [R1], R0\n");
fprintf(output, "MOV R0, BP\n");
fprintf(output, "MOV R1, 1\n");
fprintf(output, "ADD R1, R0\n");
fprintf(output, "MOV R0, [R1]\n");
fprintf(output, "MOV R1, 1\n");
fprintf(output, "ADD R0 R1\n");
fprintf(output, "MOV R1, BP\n");
fprintf(output, "MOV R2, 1\n");
fprintf(output, "ADD R2, R1\n");
fprintf(output, "MOV [R2], R0\n");
fprintf(output, "JMP WHILES1\n");
fprintf(output, "ENDWHILE1:\n");
fprintf(output, "MOV R0, 0\n");
fprintf(output, "MOV R1, BP\n");
fprintf(output, "MOV R2, 1\n");
fprintf(output, "ADD R2, R1\n");
fprintf(output, "MOV [R2], R0\n");
fprintf(output, "WHILES2:\n");
fprintf(output, "MOV R0, BP\n");
fprintf(output, "MOV R1, 1\n");
fprintf(output, "ADD R1, R0\n");
fprintf(output, "MOV R0, [R1]\n");
fprintf(output, "MOV R1, 248\n");
fprintf(output, "LT R0 R1\n");
fprintf(output, "JZ R0, ENDWHILE2\n");
fprintf(output, "MOV R0, BP\n");
fprintf(output, "MOV R1, 1\n");
fprintf(output, "ADD R1, R0\n");
fprintf(output, "MOV R0, [R1]\n");
fprintf(output, "MOV R1, 8\n");
fprintf(output, "ADD R0 R1\n");
fprintf(output, "MOV R1, BP\n");
fprintf(output, "MOV R2, 1\n");
fprintf(output, "ADD R2, R1\n");
fprintf(output, "MOV R1, [R2]\n");
fprintf(output, "MOV R2, 0\n");
fprintf(output, "ADD R1, R2\n");
fprintf(output, "MOV [R1], R0\n");
fprintf(output, "MOV R0, BP\n");
fprintf(output, "MOV R1, 1\n");
fprintf(output, "ADD R1, R0\n");
fprintf(output, "MOV R0, [R1]\n");
fprintf(output, "MOV R1, 8\n");
fprintf(output, "ADD R0 R1\n");
fprintf(output, "MOV R1, BP\n");
fprintf(output, "MOV R2, 1\n");
fprintf(output, "ADD R2, R1\n");
fprintf(output, "MOV [R2], R0\n");
fprintf(output, "JMP WHILES2\n");
fprintf(output, "ENDWHILE2:\n");
fprintf(output, "MOV R0, 0\n");
fprintf(output, "MOV R1, 1\n");
fprintf(output, "SUB R0 R1\n");
fprintf(output, "MOV R1, BP\n");
fprintf(output, "MOV R2, 1\n");
fprintf(output, "ADD R2, R1\n");
fprintf(output, "MOV R1, [R2]\n");
fprintf(output, "MOV R2, 0\n");
fprintf(output, "ADD R1, R2\n");
fprintf(output, "MOV [R1], R0\n");
fprintf(output, "MOV R0, -2\n");
fprintf(output, "MOV R1, BP\n");
fprintf(output, "ADD R0, R1\n");
fprintf(output, "MOV R1, 0\n");
fprintf(output, "MOV [R0], R1\n");
fprintf(output, "MOV SP, BP\n");
fprintf(output, "POP BP\n");
fprintf(output, "RET\n");
fprintf(output, "FUNCallocate:\n");
fprintf(output, "PUSH BP\n");
fprintf(output, "MOV BP, SP\n");
fprintf(output, "MOV R0, BP\n");
fprintf(output, "MOV R1, 1\n");
fprintf(output, "ADD R0, R1\n");
fprintf(output, "MOV SP, R0\n");
fprintf(output, "MOV R0, [256]\n");
fprintf(output, "MOV R1, BP\n");
fprintf(output, "MOV R2, 1\n");
fprintf(output, "ADD R2, R1\n");
fprintf(output, "MOV [R2], R0\n");
fprintf(output, "IFSTART1:\n");
fprintf(output, "MOV R0, [256]\n");
fprintf(output, "MOV R1, 0\n");
fprintf(output, "MOV R2, 1\n");
fprintf(output, "SUB R1 R2\n");
fprintf(output, "NE R0 R1\n");
fprintf(output, "JZ R0, ENDIF1\n");
fprintf(output, "MOV R1, [256]\n");
fprintf(output, "MOV R2, 0 \n");
fprintf(output, "ADD R1, R2\n");
fprintf(output, "MOV R1, [R1]\n");
fprintf(output, "MOV [256], R1\n");
fprintf(output, "ENDIF1:\n");
fprintf(output, "MOV R0, -2\n");
fprintf(output, "MOV R1, BP\n");
fprintf(output, "ADD R0, R1\n");
fprintf(output, "MOV R1, BP\n");
fprintf(output, "MOV R2, 1\n");
fprintf(output, "ADD R2, R1\n");
fprintf(output, "MOV R1, [R2]\n");
fprintf(output, "MOV [R0], R1\n");
fprintf(output, "MOV SP, BP\n");
fprintf(output, "POP BP\n");
fprintf(output, "RET\n");
fprintf(output, "FUNCfree:\n");
fprintf(output, "PUSH BP\n");
fprintf(output, "MOV BP, SP\n");
fprintf(output, "MOV R0, BP\n");
fprintf(output, "MOV R1, 1\n");
fprintf(output, "ADD R0, R1\n");
fprintf(output, "MOV SP, R0\n");
fprintf(output, "MOV R0, [256]\n");
fprintf(output, "MOV R1, BP\n");
fprintf(output, "MOV R2, -3\n");
fprintf(output, "ADD R2, R1\n");
fprintf(output, "MOV R1, [R2]\n");
fprintf(output, "MOV R2, 0\n");
fprintf(output, "ADD R1, R2\n");
fprintf(output, "MOV [R1], R0\n");
fprintf(output, "MOV R0, BP\n");
fprintf(output, "MOV R1, -3\n");
fprintf(output, "ADD R1, R0\n");
fprintf(output, "MOV R0, [R1]\n");
fprintf(output, "MOV [256], R0\n");
fprintf(output, "MOV R0, -2\n");
fprintf(output, "MOV R1, BP\n");
fprintf(output, "ADD R0, R1\n");
fprintf(output, "MOV R1, 0\n");
fprintf(output, "MOV [R0], R1\n");
fprintf(output, "MOV SP, BP\n");
fprintf(output, "POP BP\n");
fprintf(output, "RET"