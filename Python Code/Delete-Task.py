def delete_todo (task, todo_list):
  # removes task from the list if it is in the list
  if task in todo_list:
    todo_list.remove(task)
  return
