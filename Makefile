############
# Config
############
PROJNAME := main
SRCDIR := src
OBJDIR := obj

SOURCES:= $(wildcard $(SRCDIR)/*.cpp)
OBJECTS:= $(subst .cpp,.o,$(subst $(SRCDIR),$(OBJDIR),$(SOURCES)))
INCLUDE:= -I. -Isrc
LIBS   := -static-libstdc++ -static-libgcc -mwindows
CXX    := g++
CXXFLAGS:= -std=c++11


############
# Build
############
all: $(PROJNAME)


$(PROJNAME): $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $^ $(CXXFLAGS) $(INCLUDE) -o $@

clean:
	rm $(OBJDIR)/*.o $(PROJNAME).exe

info:
	$(info ($(subst $(SRCDIR)/,,$(SOURCES))))

infos:	
	@ls $(SRCDIR)