#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

struct DirectoryLevel {
  int directoryCounter;
  struct DirectoryLevel* next;
};

struct DirectoryLevel* root;

struct DirectoryLevel* CreateLevel() {
	struct DirectoryLevel* level = (struct DirectoryLevel*)malloc(sizeof(struct DirectoryLevel));	
	level->directoryCounter = 0;
	level->next = NULL;
}

struct DirectoryLevel* CreateRootLevel() {
	struct DirectoryLevel* level = CreateLevel();	
	level->directoryCounter = 1;
	level->next = CreateLevel();
}

void PrintResults() {
	struct DirectoryLevel* temp = root;
	
	int level = 0;
	int totalNumberOfDirectories = 0;
	while (temp != NULL) {
		printf("Razina %d: %d\n", level, temp->directoryCounter);
		totalNumberOfDirectories = totalNumberOfDirectories + temp->directoryCounter;
		temp = temp->next;
		level++;
	}
	printf("Total number of directories: %d\n", totalNumberOfDirectories);
}

void FileFound_IncrementCounter(struct DirectoryLevel* level) {
	level->directoryCounter++;
}

bool ListDirectoryContents(const char *sDir, struct DirectoryLevel *level)
{
    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;

    char sPath[2048];

    //Specify a file mask. *.* = We want everything!
    sprintf(sPath, "%s\\*.*", sDir);

    if((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
    {
        //printf("Path not found: [%s]\n", sDir);
        return false;
    }

    do
    {
        //Find first file will always return "."
        //    and ".." as the first two directories.
        if(strcmp(fdFile.cFileName, ".") != 0
                && strcmp(fdFile.cFileName, "..") != 0)
        {
            //Build up our file path using the passed in
            //  [sDir] and the file/foldername we just found:
            sprintf(sPath, "%s\\%s", sDir, fdFile.cFileName);

            //Is the entity a File or Folder?
            if(fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
            {
                //printf("Directory: %s\n", sPath);
                
                FileFound_IncrementCounter(level);
                
                if (level->next == NULL)
					level->next = CreateLevel();
                
                ListDirectoryContents(sPath, level->next);
            }
            else{
                //printf("File: %s\n", sPath);
            }
        }
    }
    while(FindNextFile(hFind, &fdFile)); //Find the next file.

    FindClose(hFind); //Always, Always, clean things up!

    return true;
}

int main() {
	root = CreateRootLevel();
	
	printf("Find out how many directories are on each level under selected directory.\n");
	printf("Example # C:\\Users\\Tomislav\\Documents\n");
	printf("Example # C:\\\n");
	printf("\n");
	printf("Enter directory path: ");
	
	char path[MAX_PATH]; // MAX_PATH is 260 characters
	
	scanf("%[^\n]%*c", path);
	
	printf("Path you have entered:\n");
	printf("%s\n", path);
	printf("----------------------------------------\n");
	
	if (ListDirectoryContents(path, root->next))	
		PrintResults();
	else
		printf("Try another path\n");
	
	printf("\n");
	system("pause");
	
	return 0;
}
