#include "utils.h"

int dict_vector_nbr = 0;
int dict_word_nbr = 0;
int new_argc;

int main(int argc, char *argv[])
{
    learn_dict_vars(DICT_FILE, 1); // 1 flag is for the number of words
    learn_dict_vars(DICT_FILE, 2); // 2 flag is for the number of vectors
    new_argc = argc; // we will use the new argc later
    int r, input_word_number; // 
    char words[INPUT_MAX_WORD][MAX_WORD_SIZE]; // this char array will hold all the words in input file
    char dict[dict_word_nbr + 1][MAX_WORD_SIZE]; // this char array will hold all the words in dictionary file
    int occurence[argc - 1]; // this array will hold the number of occoruences of each word entered
    char hist[argc][MAX_WORD_SIZE + 5 + 20]; // this array will hold the last output screen in multiple inputs

    if (argc < 2)
        return (0);
    input_word_number = read_text(INPUT_FILE, IGNORED_FILE, words);
    r = read_dict(DICT_FILE, dict); // this function will scan the dict and then will assign the word number to global variable of dict_word_number
    if (r == -1 || input_word_number == -1)
        return (0);
    if (argc == 2) // if only 1 argumen entered when program called it will get in here
    {
        occurence[0] = whats_occoruence(words, argv[1], input_word_number);
        if (occurence[0] != -1) // if its not -1 then it means it found at least one times in input.txt
            return (printf("Enter word(s): %s\n\"%s\" appears in \"%s\" %d times.\n", argv[1], argv[1], INPUT_FILE, occurence[0]), 0);
        else // else it means it didnt found the word in input.txt and we will look for its closest word
        {
            int q = find_closest(argv[1], dict); // in here we find the closest word in dict 
            if (q == -1) // if q == -1 then it means word is not at the dictionary so we cant find its closest word
                return (printf("Enter word(s): %s\n\"%s\" is not matched in \"%s\"\n", argv[1], argv[1], INPUT_FILE), 0);
            occurence[0] = whats_occoruence(words, dict[q], input_word_number); // we send the closest word to occoruence to find the times it given in input.txt
            if (occurence[0] != -1) // if this one is not -1 then we understand that closest one is occurs in input.txt and we print it 
                return (printf("Enter word(s): %s\n\"%s\" doesn't apeear in \"%s\" but \"%s\" appears %d times.\n", argv[1], argv[1], INPUT_FILE, dict[q], occurence[0]), 0);
            else if (occurence[0] == -1) // if this one also -1 then we understand closest one didnt occur in file too so we print that we couldnt find any mathes
                return (printf("Enter word(s): %s\n\"%s\" is not matched in \"%s\"\n", argv[1], argv[1], INPUT_FILE), 0);
        }
    }
    else // if multiple inputs given when program called this part will take the role and print the histogram at the end
    {
        printf("Enter word(s): "); // this part is for the user to see his own inputs
        for (int i = 1; i < argc; i++)
            printf("%s ", argv[i]);
        printf("\n");

        for (int i = 0; i < argc - 1; i++) // this loop makes it travel between words one by one and save the occorence times to the array of occoruence
        {
            occurence[i] = whats_occoruence(words, argv[i + 1], input_word_number); // we look for the occoruence and save it to the array
            if (occurence[i] == -1) // if its -1 it means it didnt found the word in input
            {
                int q = find_closest(argv[i + 1], dict); // we find the closest word
                if (q == -1)
                    occurence[i] = INT_MAX; // i use the INT_MAX as a exit value so if i see this i will print no matches
                else
                {
                    occurence[i] = whats_occoruence(words, dict[q], input_word_number);
                    if (occurence[i] == -1)
                        occurence[i] = INT_MAX; // i use the INT_MAX as a exit value so if i see this i will print no matches
                    else
                        occurence[i] = -occurence[i]; // in here i save the occur time as negative so i will understand it is not the word user inputted but we found the closest one in the input
                }
            }
        }
        fill_histogram(hist, argv, occurence, dict); // we fill the hist array
        histogram(words, occurence, hist); // we print the hist as the format in pdf 
    }
    return (0);
}

int read_dict(const char *file_name, char dict[][MAX_WORD_SIZE]) // this fucntion reads the dictionary file and saves it to the array
{
    int i = 0;
    int j = 0;
    float my_float;
    char my_char;
    char str[MAX_WORD_SIZE];

    FILE *fp = fopen(file_name, "r");
    while (fscanf(fp, "%c", &my_char) != -1 && my_char != '\n')
        ;
    while (i < dict_word_nbr)
    {
        fscanf(fp, "%s", str);
        if (my_assign_fnct(dict, str, i) == -1) // assign str to arrays assigns the str value to dict's i'th index one by one
        {
            fclose(fp); // it get in here when there is  a error assigning to array
            return (-1);
        }
        for (j = 0; j < dict_vector_nbr; j++)
            fscanf(fp, "%f", &my_float);
        i++;
    }
    dict[i][0] = '-';// we add the sentiel value
    fclose(fp);
    return (i);
}

int read_text(const char *text_file, const char *ignore_file, char words[][MAX_WORD_SIZE]) // this fucntion reads the input file and save words to array
{
    int i = 0;
    int count = 0;
    char ch;
    float tmp;
    FILE *text = fopen(text_file, "r");
    char str[MAX_WORD_SIZE];

    while (fscanf(text, "%c", &ch) != -1)
    {
        if (ch != '\n' && ch != ' ')
        {
            if (check_ignore_letters(ch) == 1) // we pass the ignored letters
            {
                str[i] = ch;
                i++;
            }
        }
        else
        {
            str[i] = '\0';
            i = 0;
            if (check_is_ignored(str) == 1 && (str[0] != '\0')) // check_is_ignored goes to the ignored file and returns 1 if exist
            {
                my_assign_fnct(words, str, count); // we assign the word to the array of words
                count++;
            }
        }
    }
    fclose(text);
    return (count);
}

int find_line(char *str, char dict[][MAX_WORD_SIZE]) // this funciton goes to the dict array and returns the line it founds the given string
{
    for (int i = 0; i < dict_word_nbr; i++)
        if (strcmp(str, dict[i]) == 0)
            return i;
    return -1;
}

void	fill_vectors(double vectors[][dict_vector_nbr]) //fill the vectors array with a word's vector values
{
	FILE	*file = fopen(DICT_FILE, "r");
	int		i = 0;
	char	letter;
    char    str[MAX_WORD_SIZE];

	while (fscanf(file, "%c", &letter) != -1 && letter != '\n');// skips the first line
	while (i < dict_word_nbr)
    {
		fscanf(file, "%s", str);// skips the word
		for (int j = 0; j < dict_vector_nbr; j++)// reads vectors
			fscanf(file, "%lf", &vectors[i][j]);
		i++;
	}
    fclose(file);
}

double	calculate_distance(double vector1[], double vector2[]) //calculates the distance between given vectors
{
	double sum = 0, temp = 0;
	for (int i = 0; i < dict_vector_nbr; i++)
    {
		temp = vector1[i] - vector2[i];
		sum += temp * temp;
		if (sum > THRESHOLD * THRESHOLD) // if sum bigegr than thershold square then it means it too far to me closest one
            return (INT_MAX);
	}
	sum = sqrt(sum);
	return (sum);
}

double dissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], double threshold) //this function, calculates the distance between given word with other word
{
	int	i = 0, line;
	double vectors[dict_word_nbr][dict_vector_nbr], temp;
    int min_line = 0;
	double sum = INT_MAX;
	line = find_line(w1, dict);
	fill_vectors(vectors);
	while (i < dict_word_nbr)
    {
		if (i != line)
        {
			temp = calculate_distance(vectors[line], vectors[i]);
			if(temp < sum) // if temp is smaller then sum then temp should be the new sum
			{
				sum = temp;
				min_line = i; // we change the new minimum line
			}
		}
		i++;
	}
	strcpy(w2, dict[min_line]); // we save w2 string to dictionary 
	return (min_line); // we return the line value of closest word
}

int check_is_ignored(char word[]) // checks for if a word is in ignored file or not
{

    FILE *file = fopen(IGNORED_FILE, "r");
    char str[MAX_WORD_SIZE];

    while (fscanf(file, "%s", str) != -1)
        if (strcmp(word, str) == 0)
            return (fclose(file), 0);

    fclose(file);
    return (1);
}

int check_ignore_letters(char ch) // checks for a char is ignored letter or not
{
    if ((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A'))
        return (1);
    return (0);
}

int my_assign_fnct(char arr[][MAX_WORD_SIZE], char str[], int indx) // this is a replica of the strcpy with different logic
{
    int i = 0;

    if (!str)
        return (-1);

    while (str[i] != '\0')
    {
        arr[indx][i] = str[i];
        i++;
    }
    arr[indx][i] = '\0';
    return (1);
}

int whats_occoruence(char words[][MAX_WORD_SIZE], char *str, int input_word_number) // this fonction looks a word in input file
{
    int count = 0;

    for (int i = 0; i < input_word_number; i++)
        if (strcmp(str, words[i]) == 0)
            count++;
    if (count == 0)
        return (-1);
    return (count);
}

int find_closest(char *str, char dict[][MAX_WORD_SIZE]) // this function finds the closest word and returns the closest one
{

	double	min = -1, i = 0;
	char	answer[MAX_WORD_SIZE];
	int		return_value = 0;
	int		line;

	// for (int k = 0; k < MAX_WORD_SIZE; k++)
    //     answer[k] = '\0';

	line = find_line(str, dict);
	if (line == -1)
        return (line);
	//printf("line : %d\n", line);
	min = dissimilarity(dict[line], answer, dict, THRESHOLD);
	return_value = find_line(answer, dict);
	return (return_value);
}

void learn_dict_vars(char *file_name, int flag) // this is for the first line infos in dict
{
    FILE *file = fopen(file_name, "r");
    char str[50];
    int res = 0, len = 0;

    for (int i = 0; i < flag; i++)
    {
        fscanf(file, "%s", str);
    }
    len = ft_strlen(str);
    res = ft_atoi(str, len);
    if (flag == 1)
    {
        dict_word_nbr = res;
    }
    else if (flag == 2)
    {
        dict_vector_nbr = res;
    }
    fclose(file);
}

int ft_strlen(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

int ft_atoi(const char *str, int len)
{
    int res = 0;
    while (str[len] != '=')
        len--;
    len++;
    while (str[len] != ',' && str[len] != '\0')
    {
        res = (res * 10) + (str[len] - '0');
        len++;
    }
    return (res);
}

int histogram(const char words[][MAX_WORD_SIZE], const int occurrences[], const char hist[][MAX_WORD_SIZE + 5 + 20])
{
    int scale = 1;
    int max = 1;
    int size = new_argc;
    for (int i = 0; i < size - 1; i++)
    {
        if ((abs(occurrences[i]) > max) && occurrences[i] != INT_MAX)
            max = abs(occurrences[i]);
    }
    if (max % 20 == 0)
        scale = max / 20;
    else
        scale = (max / 20) + 1;
    if (scale != 1)
        printf("Scale: %d\n", scale);
    for (int i = 0; i < new_argc - 1; i++)
    {
        printf("%s", hist[i]);
        if (occurrences[i] < 0 && occurrences[i] != INT_MAX)
            for (int j = 0; j < abs(occurrences[i]) / scale; j++)
                printf("+");
        else if (occurrences[i] != INT_MAX)
            for (int j = 0; j < abs(occurrences[i]) / scale; j++)
                printf("*");
        else if (occurrences[i] == INT_MAX)
            printf("NO MATCHES");
        printf("\n");
    }
    return (scale);
}

void fill_histogram(char hist[][MAX_WORD_SIZE + 5 + 20], char *argv[], const int occurence[], char dict[][MAX_WORD_SIZE])
{
    int i = 1;
    int j = 0;
    while (i < new_argc)
    {
        j = 1;
        hist[i - 1][0] = '"';
        while (argv[i][j - 1] != '\0')
        {
            hist[i - 1][j] = argv[i][j - 1];
            j++;
        }
        if (occurence[i - 1] > 0)
            hist[i - 1][j] = '"';
        else
        {
            hist[i - 1][j] = '-';
            j++;
            hist[i - 1][j] = '>';
            j++;
            int k = 0;
            int q = find_closest(argv[i], dict);
            while (dict[q][k] != '\0')
            {
                hist[i - 1][j] = dict[q][k];
                k++;
                j++;
            }
            hist[i - 1][j] = '"';
        }
        j++;
        while (j < MAX_WORD_SIZE * 1.5)
        {
            hist[i - 1][j] = ' ';
            j++;
        }
        hist[i - 1][j] = '\0';
        i++;
    }
    hist[i - 1][0] = '#';
}

int ft_strcat(char *dest, char *src, int j) // str cat is like strcpy but it writes to the and not over the first text
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[j] = src[i];
        i++;
        j++;
    }
    return (j);
}
