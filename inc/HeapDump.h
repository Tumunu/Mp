#include <f32file.h>

class RHackedHeap : public RHeap
	{
public:
	RHackedHeap();
	using RHeap::iFree;
	using RHeap::iTop;
	using RHeap::GetAddress;
	};


void HeapDump()
	{
	// get the local thread
	RThread thread;
	RHackedHeap& heap = *(RHackedHeap*)thread.Heap();

	// create a filename C:\threadName_threadId.heap
	TName threadName = thread.Name();
	TName name;
	name.Num(thread.Id());
	name.Insert(0, _L("_"));
	name.Insert(0, threadName);
	name.Insert(0,_L("C:\\"));
	name.Append(_L(".heap"));

	// Open the file
	RFs fs;
	fs.Connect();
	fs.Delete(name);
	RFile f;
	f.Create(fs,name,EFileWrite);

	// calculate heap cell header size
	TUint8* ptr = (TUint8*)heap.Alloc(4);
	TInt cellSize = ptr - ((TUint8*)heap.GetAddress(ptr));
	heap.Free(ptr);

	// write out the heap file in the following format:
	// 4 bytes: base address of the heap
	// 4 bytes: first free cell address in the heap
	// 4 bytes: top address of the heap
	// 4 bytes: heap cell header size
	// 4 bytes: heap size (n)
	// n bytes: heap contents
	// The following is repeated till the end of the file for all chunks associated with the thread
	// 4 bytes: base address of the chunk
	// 4 bytes: size of the chunk
	TUint8* base = heap.Base();
	f.Write(TPtrC8((TUint8*)&base, 4));
	TUint8* free = (TUint8*)heap.iFree.next;
	f.Write(TPtrC8((TUint8*)&free, 4));
	TUint8* top = heap.iTop;
	f.Write(TPtrC8((TUint8*)&top, 4));
	f.Write(TPtrC8((TUint8*)&cellSize, 4));
	TInt size = heap.Size();
	f.Write(TPtrC8((TUint8*)&size, 4));
	f.Write(TPtrC8((TUint8*)base, size));

	// find the chunks loaded
	TFullName chname;
	chname.Format(_L("*%S*"),&threadName);
	TFindChunk findChunk(chname);
	RChunk chunk;
	while (findChunk.Next(chname)==KErrNone)
		{
		if (chunk.Open(findChunk) == KErrNone)
			{
			TUint8* base = chunk.Base();
			f.Write(TPtrC8((TUint8*)&base, 4));
			TInt size = chunk.Size();
			f.Write(TPtrC8((TUint8*)&size, 4));
			chunk.Close();
			}
		}

	// tidy up
	f.Flush();
	f.Close();
	fs.Close();
	}

