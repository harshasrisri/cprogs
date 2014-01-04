/*=====================================
  C function to split a line into a bunch of words
  =====================================*/

# include <header.h>

int line_2_words (char ***words, char *line, char delim) {
	char **sentence = NULL, *temp, *save, c;
	int word_count = 0, white = 1;

	if ((!line) || (!*line)) {
		return 0;
	}

	temp = (char *) malloc (50);
	save = temp;
	while (1) {
		c = *line++;
		if ((c == delim) || (c == '\0')) {
			white = 1;
			if (c == delim) continue;
		} 
		if (white) {
			white = 0;
			if (!(word_count % 10)) {
				sentence = (char **) realloc (sentence, (word_count + 10) * sizeof (char *));
			}
			*temp = '\0';
			if (*save) {
				temp = save;
				sentence[word_count++] = strdup(temp);
			}
			if ((c == '\0')) break;
		}
		*temp++ = c;
	}
	if (sentence) {
		sentence[word_count + 1] = '\0';
	}
	*words = sentence;
	return word_count;
}
