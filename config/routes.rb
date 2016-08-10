Rails.application.routes.draw do
  resource :githook, only: :create, defaults: { formats: :json }
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
